package org.example;

import java.sql.*;

//工具类
public class DataUtil {
    private static String url = "jdbc:mysql://127.0.0.1:3306/db1";
    private static String username = "root";
    private static String password = "123456";
    //由于静态方法只能调用静态方法，所以得将url、username、password设置成静态成员变量
    //静态方法：getConnection，用于注册驱动
    public static Connection getConnection() throws Exception {
        Connection conn = DriverManager.getConnection(url, username, password);
        return conn;
    }
}
