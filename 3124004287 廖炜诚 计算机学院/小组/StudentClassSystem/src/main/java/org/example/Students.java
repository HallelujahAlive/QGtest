package org.example;
//学生
public class Students{
    private int sid;
    private int userID;   //学生类的userID与用户表的userID同名，一个作为外键一个作为主键
    private String name;
    private String phoneNumber;

    public Students() {
    }

    public Students(int sid, int userID, String name, String phoneNumber) {
        this.sid = sid;
        this.userID = userID;
        this.name = name;
        this.phoneNumber = phoneNumber;
    }

    public int getSid() {
        return sid;
    }

    public void setSid(int sid) {
        this.sid = sid;
    }

    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}
