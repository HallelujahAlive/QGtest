package org.example;
//用户与学生是一对一关系，userID为主键，学生表通过表中的userID与用户表连接起来
public class Users {
    private int userID;
    private String username;       //用户名
    private String password;       //用户密码
    private String role;      //1代表学生，2代表管理员

    public Users() {
    }

    public Users(int userID, String username, String password, String role) {
        this.userID = userID;
        this.username = username;
        this.password = password;
        this.role = role;
    }

    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }
}
