package org.example;

public class Course {
    private int cid;
    private String courseName;   //课程名字
    private String teacherName;  //授课老师姓名
    private double scores;       //学分
    private String place;        //上课地点
    private String time;         //上课时间
    private String status;       //课程状态：是否开课

    public Course() {
    }

    public Course(int cid, String courseName, String teacherName, double scores, String place, String time, String status) {
        this.cid = cid;
        this.courseName = courseName;
        this.teacherName = teacherName;
        this.scores = scores;
        this.place = place;
        this.time = time;
        this.status = status;
    }

    public int getCid() {
        return cid;
    }

    public void setCid(int cid) {
        this.cid = cid;
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCourseName(String courseName) {
        this.courseName = courseName;
    }

    public String getTeacherName() {
        return teacherName;
    }

    public void setTeacherName(String teacherName) {
        this.teacherName = teacherName;
    }

    public double getScores() {
        return scores;
    }

    public void setScores(double scores) {
        this.scores = scores;
    }

    public String getPlace() {
        return place;
    }

    public void setPlace(String place) {
        this.place = place;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
