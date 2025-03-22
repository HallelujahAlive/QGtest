package org.example;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.InputMismatchException;
import java.util.Scanner;


public class System
{
    //因为几乎所有方法都要用到Scanner对象，所以我想将scanner定义在类之内，方法外
    private static Scanner sc = new Scanner(java.lang.System.in);
    //考虑到登录之后仍然需要用到Users对象，所以我将Users对象作为成员变量放到方法外，因为静态方法只能调用静态方法，所以我将这个成员变量用private static修饰
    private static Users user = null;
    public static void main( String[] args )
    {
        while (true) {
            java.lang.System.out.println("===========================");
            java.lang.System.out.println("     学生选课管理系统     ");
            java.lang.System.out.println("===========================");
            java.lang.System.out.println("1. 登录");
            java.lang.System.out.println("2. 注册");
            java.lang.System.out.println("3. 退出");
            java.lang.System.out.print("请选择操作（输入 1-3）：");

            int choice = sc.nextInt();
            sc.nextLine();
            switch (choice){
                case 1:
                    login();
                    break;
                case 2:
                    register();
                    break;
                case 3:
                    java.lang.System.out.println("退出系统");
                    sc.close(); // 释放Scanner，避免浪费资源
                    return;
                default:
                    java.lang.System.out.println("没有该选项，请重新输入！");
            }
            //清理缓冲区
            sc.nextLine();
        }
    }

    private static void login() {
        java.lang.System.out.println("===== 用户登录 =====");
        java.lang.System.out.print("请输入用户名：");
        //用户名和密码都可以含有空格
        String username = sc.nextLine();
        java.lang.System.out.print("请输入密码：");
        java.lang.String password = sc.nextLine();
        //通过sql语句将用户名和密码传递给数据库
        String sql = "select * from users where username = ? and password = ?";
        //防止sql注入
        //使用异常处理机制，抛出异常（而且抛出大的异常Exception防止出现除sql语句外的其他问题而导致程序崩溃）
        try (Connection conn = DataUtil.getConnection()){
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置参数username和password
            pstmt.setString(1,username);
            pstmt.setString(2,password);
            //调用查询方法：executeQuery(),注意，这里由于前面已经传入了sql语句，所以不再需要再传入sql语句
            ResultSet rs = pstmt.executeQuery();
            //如果rs.next()返回的boolean为true，说明该用户存在，可以登录系统
            user = new Users();
            if (rs.next()){
                user.setUserID(rs.getInt("userID"));
                user.setUsername(rs.getString("username"));
                user.setPassword(rs.getString("password"));
                user.setRole(rs.getString("role"));
                //根据role决定进入管理员界面还是学生界面
                java.lang.System.out.println("登录成功！您的身份是"+user.getRole());
                if (user.getRole().equals("student")){
                    studentMenu();
                } else if (user.getRole().equals("admin")){
                    adminMenu();
                } else {
                    java.lang.System.out.println("用户名或密码错误，登陆失败！");
                }
            }
            //释放资源
            rs.close();
            pstmt.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        sc.nextLine();
    }

    private static void register(){
        //使用异常处理，抛出异常
        try (Connection conn = DataUtil.getConnection()) {
            java.lang.System.out.println("===== 用户注册 =====");
            java.lang.System.out.print("请输入用户名：");
            String username = sc.nextLine();
            java.lang.System.out.print("请输入密码：");
            String password = sc.nextLine();
            java.lang.System.out.print("请确认密码：");
            String confirmPassword = sc.nextLine();
            java.lang.System.out.print("请选择角色（输入 1 代表学生，2 代表管理员）：");
            int roleChoice = sc.nextInt();
            //为确保正确输入流(如果混合使用nextInt和nextLine，可能会导致输入流未处理正确，从而跳过某些输入)
            sc.nextLine();                           //清理输入缓冲区

            if (!password.equals(confirmPassword)){
                java.lang.System.out.println("两次密码输入不匹配!");
                return;
            }
            //如果用户选择的是1，那么赋予角色“学生”，如果选择2，赋予角色“管理员”，否则提示错误并返回登陆注册页面
            String role;
            if (roleChoice == 1){
                role = "student";
            } else if (roleChoice == 2){
                role = "admin";
            } else {
                java.lang.System.out.println("没有该角色!");
                return;
            }
            //如果注册成功，那么将新用户的信息传入数据库
            //定义sql语句:insert
            String sql = "insert into users(username,password,role) values(?,?,?)";
            //将定义的sql语句传入，同时利用prepareStatement对象返回插入新数据后自动生成的userID
            PreparedStatement pstmt1 = conn.prepareStatement(sql,PreparedStatement.RETURN_GENERATED_KEYS);
            //传参
            pstmt1.setString(1,username);
            pstmt1.setString(2,password);
            pstmt1.setString(3,role);
            //调用修改方法：executeUpdate(),还是注意不用传入sql语句
            //executeUpdate作用：插入、修改、删除数据，并返回一个整数值，表示受影响的行数
            int i = pstmt1.executeUpdate();
            if (i<=0){
                java.lang.System.out.println("注册失败!");
                return;
            }

            /*如果注册用户选择的是学生身份，要求输入自己的姓名和手机号码
            同时需要得到数据库自动生成的userID
            最后将学生的userID、姓名和手机号码插入学生表(insert)
            释放资源*/
            //获取生成的userID
            ResultSet rs = pstmt1.getGeneratedKeys();
            int userID = -1;
            if (rs.next()){
                userID = rs.getInt(1);
            }
            //确定是否是学生身份
            if (role.equals("student")){
                java.lang.System.out.print("请输入你的真实姓名：");
                String name = sc.nextLine();
                java.lang.System.out.print("请输入你的手机号码：");
                String phoneNumber = sc.nextLine();
                //定义sql语句，将学生的新数据插入学生表
                String stuSQL = "insert into students(userID,name,phoneNumber) values(?,?,?)";
                PreparedStatement pstmt2 = conn.prepareStatement(stuSQL);
                pstmt2.setInt(1,userID);
                pstmt2.setString(2,name);
                pstmt2.setString(3,phoneNumber);
                pstmt2.executeUpdate();
                //释放资源
                pstmt2.close();
            }
            //释放资源
            rs.close();
            pstmt1.close();
            conn.close();
            java.lang.System.out.println("注册成功，请前往登录进入系统！");
        } catch (InputMismatchException e){
            java.lang.System.out.println("请勿输入无效数字，请稍后重试！");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static void studentMenu() {
        while (true) {
            java.lang.System.out.println("===== 学生菜单 =====");
            java.lang.System.out.println("1. 查看可选课程");
            java.lang.System.out.println("2. 选择课程");
            java.lang.System.out.println("3. 退选课程");
            java.lang.System.out.println("4. 查看已选课程");
            java.lang.System.out.println("5. 修改手机号");
            java.lang.System.out.println("6. 退出");
            java.lang.System.out.print("请选择操作（输入 1-6）：");

            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    //查看已开放的课程
                    checkAvailableCourses();
                    break;
                case 2:
                    //选择课程
                    selectCourse();
                    break;
                case 3:
                    //退选课程
                    dropCourse();
                    break;
                case 4:
                    //查看已选课程
                    checkSelectedCourses();
                    break;
                case 5:
                    //修改手机号码
                    changePhoneNumber();
                    break;
                case 6:
                    return;
                default:
                    java.lang.System.out.println("没有该选项，请重新输入！");
            }
        }
    }

    private static void adminMenu() {
        while (true) {
            java.lang.System.out.println("===== 管理员菜单 =====");
            java.lang.System.out.println("1. 查询所有学生");
            java.lang.System.out.println("2. 修改学生手机号");
            java.lang.System.out.println("3. 查询所有课程");
            java.lang.System.out.println("4. 修改课程学分");
            java.lang.System.out.println("5. 查询某课程的学生名单");
            java.lang.System.out.println("6. 查询某学生的选课情况");
            java.lang.System.out.println("7. 退出");
            java.lang.System.out.print("请选择操作（输入 1-7）：");

            int choice = sc.nextInt();
            switch (choice){
                case 1:
                    //查询所有学生
                    checkAllStudents();
                    break;
                case 2:
                    //修改学生手机号
                    changeStudentPhoneNumber();
                    break;
                case 3:
                    //查询所有课程
                    checkAllCourses();
                    break;
                case 4:
                    //修改课程学分
                    changeCourseScores();
                    break;
                case 5:
                    //查询某课程的学生名单
                    checkStudentsInCourse();
                    break;
                case 6:
                    //查询某学生的选课情况
                    checkStudentCourses();
                    break;
                case 7:
                    return;
                default:
                    java.lang.System.out.println("没有该选项，请重新输入");
            }
        }

    }

    //管理员部分
    //查询所有学生
    private static void checkAllStudents() {
        try (Connection conn = DataUtil.getConnection()) {
            String sql = "select * from students";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()){
                int sid = rs.getInt("sid");
                int userID = rs.getInt("userID");
                String name = rs.getString("name");
                String phoneNumber = rs.getString("phoneNumber");
                java.lang.System.out.println("学生序号："+sid+" 用户序号："+userID+" 学生姓名："+name+" 手机号："+phoneNumber);
            }
            //释放资源
            rs.close();
            pstmt.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    //修改学生手机号码
    private static void changeStudentPhoneNumber() {
        try (Connection conn = DataUtil.getConnection()) {
            //展示所有学生的信息，方便管理员知道要改哪位学生的手机号码
            checkAllStudents();
            //展示完所有学生的信息之后，管理员输入要修改的那位学生的序号
            java.lang.System.out.println("请输入你要修改的学生的序号：");
            int sid = sc.nextInt();
            String querySql = "select phoneNumber from students where sid = ?";
            PreparedStatement queryPstmt = conn.prepareStatement(querySql);
            //设置参数
            queryPstmt.setInt(1,sid);
            ResultSet rs = queryPstmt.executeQuery();
            if (rs.next()) {
                java.lang.System.out.println("您要修改的学生的原手机号码为"+rs.getString("phoneNumber")
                +"，请输入新手机号码：");
                String newPhoneNumber = sc.next();
                String updateSql = "update students set phoneNumber = ?";
                PreparedStatement updatePstmt = conn.prepareStatement(updateSql);
                //设置参数
                updatePstmt.setString(1,newPhoneNumber);
                int i = updatePstmt.executeUpdate();
                if (i > 0) {
                    java.lang.System.out.println("手机号修改成功！");
                } else {
                    java.lang.System.out.println("手机号码修改失败！");
                }
                //释放资源
                updatePstmt.close();
            } else {
                java.lang.System.out.println("该学生不存在，无法修改手机号码！");
            }
            //释放资源
            rs.close();
            queryPstmt.close();
        } catch (InputMismatchException e){
            java.lang.System.out.println("请勿输入无效数字，请稍后重试！");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //查询所有课程
    private static void checkAllCourses() {
        try (Connection conn = DataUtil.getConnection()){
            //定义sql语句
            String sql = "select * from courses";
            //创建执行sql语句的对象
            PreparedStatement pstmt = conn.prepareStatement(sql);
            printCourse(pstmt);
            pstmt.close();
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    //修改课程学分
    private static void changeCourseScores() {
        try (Connection conn = DataUtil.getConnection()) {
            //先展示所有课程的信息
            checkAllCourses();
            //展示完所有课程的信息后，管理员输入想要修改的课程的序号
            java.lang.System.out.println("请输入你要修改的课程对应的序号：");
            int cid = sc.nextInt();
            String querySql = "select scores from courses where cid = ?";
            PreparedStatement queryPstmt = conn.prepareStatement(querySql);
            queryPstmt.setInt(1,cid);
            ResultSet rs = queryPstmt.executeQuery();

            //如果rs.next()不为false，说明该课程存在，可以修改学分
            if (rs.next()){

                java.lang.System.out.println("您要修改的课程是"+rs.getString("scores")+"，请输入你要修改的学分：");
                double updateScores = sc.nextDouble();
                String updateSql = "update courses set scores = ? where cid = ?";
                PreparedStatement updatePstmt = conn.prepareStatement(updateSql);
                updatePstmt.setDouble(1,updateScores);
                updatePstmt.setInt(2,cid);
                updatePstmt.executeUpdate();
                java.lang.System.out.println("学分修改成功！");

                //释放资源
                updatePstmt.close();
                queryPstmt.close();
            } else {
                java.lang.System.out.println("未找到该课程！");
            }
        } catch (InputMismatchException e){
            java.lang.System.out.println("请勿输入无效数字，请稍后重试！");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //查询某课程的学生名单
    private static void checkStudentsInCourse() {
        try (Connection conn = DataUtil.getConnection()){
            //首先打印所有可选课程信息，让管理员能够知道想要查看的课程所对应的序号
            checkAvailableCourses();
            java.lang.System.out.println("请输入你要查询的课程的序号：");
            int cid = sc.nextInt();
            //这里要用到多表查询，1,首先需要通过课程的序号在students_courses表中获取对应的学生序号sid
            //2,然后通过获得的sid在学生表students中查询等于sid的学生并打印这些学生的名字
            String sql = "select name from students where sid = (select sid from students_courses where cid = ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置参数
            pstmt.setInt(1,cid);
            ResultSet rs = pstmt.executeQuery();
            if (!rs.next()){
                java.lang.System.out.println("该课程还没有学生选择！");
            } else {
                do {
                    String name = rs.getString("name");
                    java.lang.System.out.println(name);
                } while (rs.next());
            }
            rs.close();
            pstmt.close();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    //查询某学生的选课情况
    private static void checkStudentCourses() {
        try (Connection conn = DataUtil.getConnection()){
            //首先打印所有学生出来，以便管理员知道所要查看的学生的序号是多少
            checkAllStudents();
            //当看完学生名单后，管理员应当知道了要查看的学生的学号
            java.lang.System.out.println("请输入你要查看的学生的序号:");
            int sid = sc.nextInt();
            //多表查询之子查询：一个select语句之中还有一个select语句
            //要查某学生的选课情况，1,首先需要知道学生的序号
            //2,知道序号之后，要根据需要在students_courses表中知道该序号所对应的cid(课程序号)
            //3,知道了课程序号之后，要根据课程序号在courses表中查询课程并打印出来
            String sql = "select * from courses where cid = (select cid from students_courses where sid = ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,sid);
            //打印该学生所选的课程信息
            printCourse(pstmt);
            pstmt.close();
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //学生部分
    //查看可选课程
    private static void checkAvailableCourses() {
        try (Connection conn = DataUtil.getConnection()){
            String sql = "select * from courses where status = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1,"可选");
            //打印信息
            printCourse(pstmt);
            pstmt.close();
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //选择课程
    //每个学生最多只能选择5门课程，且只能选择可选课程
    private static void selectCourse() {
        //只有学生才能选课，管理员不能选课
        if (!user.getRole().equals("student")){
            java.lang.System.out.println("只有学生才能选课！");
        }
        //通过当前用户的id，找到该用户在数据库学生表对应的studentID
        int sid = getStudentID(user.getUserID());
        if (sid == -1){
            java.lang.System.out.println("数据错误，请稍后重试！");
            return;
        }
        //通过得到的sid，从students_courses中统计该学生已选的课程数
        int selectCoursesCount = getSelectCoursesCount(sid);
        if (selectCoursesCount >= 5){
            java.lang.System.out.println("您当前选择的课程已满5门！不支持继续选课！");
            return;
        }
        //打印当前可选的课程信息，然后让学生输入想要选择的课程对应的序号(cid)
        checkAvailableCourses();
        java.lang.System.out.println("请输入您要选择的课程对应的序号：");
        int cid = sc.nextInt();
        //通过cid查看该课程是否存在
        boolean Exist = checkCourseExist(cid);
        if (!Exist){
            //课程不存在，报错提示并结束
            java.lang.System.out.println("该课程不存在，请稍后重试！");
            return;
        }
        //查看学生所选的课程之前有没有被选过，防止重复选择课程
        boolean repeat = checkCourseRepeat(sid, cid);
        if (repeat){       //如果重复选择，那么报错，提示用户重复选择了课程，操作失败
            java.lang.System.out.println("您已选择过该课程，选择失败！");
            return;
        }
        //以上步骤如果都通过，说明用户满足所有条件，可以选择该课程，将学生的序号和相应的课程序号录入选课表，同时提示用户选课成功
        int result = insertSelectInfo(sid, cid);
        if (result > 0){
            java.lang.System.out.println("选课成功！");
        } else {
            java.lang.System.out.println("选课失败，请稍后再试！");
        }
        //清理缓冲区
        sc.nextLine();
    }

    //选择课程的子方法5：选课成功，将选课信息插入数据库的选课表
    private static int insertSelectInfo(int sid, int cid) {
        try (Connection conn = DataUtil.getConnection()){
            String sql = "insert into students_courses(sid,cid) values(?,?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,sid);
            pstmt.setInt(2,cid);
            int i = pstmt.executeUpdate();
            //如果修改成功，则返回的i值必定大于0，如果修改失败返回的值为0
            pstmt.close();
            return i;
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //选择课程的子方法4：查看选课是否重复，重复则返回true，不重复返回false
    private static boolean checkCourseRepeat(int sid, int cid) {
        try (Connection conn = DataUtil.getConnection()){
            String sql = "select * from students_courses where sid = ? and cid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置参数
            pstmt.setInt(1,sid);
            pstmt.setInt(2,cid);
            ResultSet rs = pstmt.executeQuery();
            //返回true，说明该学生已经选过该课程，返回false则说明学生未选择过该课程
            return rs.next();
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //选择课程子方法3：检查学生所选的该课程是否存在
    private static boolean checkCourseExist(int cid) {
        try (Connection conn = DataUtil.getConnection()) {
            String sql = "select * from courses where cid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,cid);
            ResultSet rs = pstmt.executeQuery();
            return rs.next();                                                                                                                                                                //如果该课程存在，返回true，不存在则返回false
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //选择课程子方法2：查询得到该学生所选课程数目
    private static int getSelectCoursesCount(int sid) {
        try (Connection conn = DataUtil.getConnection()) {
            //需要用到聚合函数count(*)用来统计选课表中该学生所选的课程数,这里还要给count(*)起一个别名，用As ...
            String sql = "select count(*) As count from students_courses where sid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,sid);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()){
                int count = rs.getInt("count");
                return count;
            }
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
        return 0;
    }

    //选择课程的子方法1：查询返回studentID
    private static int getStudentID(int userID) {
        try (Connection conn = DataUtil.getConnection()){
            String sql = "select sid from students where userID = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,userID);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()){
                int sid = rs.getInt("sid");
                rs.close();
                pstmt.close();
                return sid;
            }
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
        return -1;
    }

    //退选课程:本质上就是删除students_courses表的数据
    private static void dropCourse() {
        //只有学生才能退选课程
        if (!user.getRole().equals("student")){
            java.lang.System.out.println("只有学生才能退选课程！");
        }
        //通过当前用户id，找到该用户对应的学生id，需要调用方法：getStudentID
        int sid = getStudentID(user.getUserID());
        if (sid <= 0){
            java.lang.System.out.println("数据错误，请稍后重试！");
            return;
        }
        //查看用户已选的课程，返回count，如果count==0，说明学生没有课程可退选，结束操作；反之，可继续操作
        //调用方法getSelectedCoursesCount，得到该学生所选的课程数目
        int count = getSelectCoursesCount(sid);
        if (!(count > 0)){
            java.lang.System.out.println("您还没选课，选课后才能进行退选！");
            return;
        }
        //打印用户当前已选的课程，然后让学生输入想要退选的课程对应的序号(cid)
        checkSelectedCourses();
        java.lang.System.out.println("请输入您要退选的课程对应的序号：");
        int cid = sc.nextInt();
        //查看当前课程是否在该学生所选的课程中
        //这里我可以偷懒，使用checkCourseRepeat来检查用户想要退选的课程是否在用户已选的课程中，如果返回true，说明在用户已选的课程中，可退选
        boolean exist = checkCourseRepeat(sid, cid);
        if (!exist){
            java.lang.System.out.println("您要退选的课程并不在已选的课程中，无法退选，请稍后重试！");
            return;
        }
        //最后一步：删除对应的students_courses表中数据
        int i = dropSelectedInfo(sid, cid);
        if (i > 0){
            java.lang.System.out.println("退选成功！");
        } else {
            java.lang.System.out.println("退选失败，请稍后再试！");
        }
        sc.nextLine();
    }

    private static int dropSelectedInfo(int sid, int cid) {
        try (Connection conn = DataUtil.getConnection()){
            String sql = "delete from students_courses where sid = ? and cid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,sid);
            pstmt.setInt(2,cid);
            int i = pstmt.executeUpdate();         //返回受影响的行数
            pstmt.close();
            return i;
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //查询已选课程
    private static void checkSelectedCourses() {
        try (Connection conn = DataUtil.getConnection()){
            //首先需要调用user.getUserID()得到该用户的userID，由于students跟users是连接起来的，所以根据userID得到sid
            //调用getStudentID，返回得到sid
            int sid = getStudentID(user.getUserID());
            //得到sid后，通过sid在students_courses表中找到sid对应的cid
            //得到cid后，再根据cid再course表中找到该用户所选课程
            String sql = "select * from courses where cid in(select cid from students_courses where sid = ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1,sid);
            printCourse(pstmt);
            pstmt.close();
            sc.nextLine();
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //修改手机号码
    private static void changePhoneNumber() {
        try (Connection conn = DataUtil.getConnection()) {
            java.lang.System.out.println("请输入新的手机号码：");
            String newPhoneNumber = sc.next();
            //登录的时候记录的用户信息仍然存在，可以直接调用user的get方法得到用户各个信息
            int userID = user.getUserID();
            String sql = "update students set phoneNumber = ? where userID = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            //设置参数
            pstmt.setString(1,newPhoneNumber);
            pstmt.setInt(2,userID);
            
            int i = pstmt.executeUpdate();
            //若i大于0，说明该用户（学生）的手机号码修改成功，如果不大于0说明修改失败
            if (i > 0){
                java.lang.System.out.println("手机号码修改成功！");
            } else {
                java.lang.System.out.println("手机号码修改失败");
            }
            pstmt.close();
            sc.nextLine();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    //供查询所有课程和查询可选课程打印用的方法
    private static void printCourse(PreparedStatement pstmt){
        try {
            ResultSet rs = pstmt.executeQuery();
            if(!rs.next()){
                java.lang.System.out.println("结果集为空，请稍后重试！");
            } else {
                do {
                    int cid = rs.getInt("cid");                        //课程序号
                    String courseName = rs.getString("courseName");    //课程名称
                    String teacherName = rs.getString("teacherName");  //授课老师姓名
                    double scores = rs.getDouble("scores");            //课程学分
                    String place = rs.getString("place");              //上课地点
                    String time = rs.getString("time");                //上课时间
                    String status = rs.getString("status");            //课程是否开课
                    java.lang.System.out.println("课程序号："+cid+" 课程名称:"+courseName+" 授课老师姓名:"+
                            teacherName+" 课程学分:"+scores+" 上课地点:"+place+" 上课时间："+time+" 状态："+status);
                } while(rs.next());
            }
            //释放资源
            rs.close();
            pstmt.close();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
