package com.example.investbank.model;

public class Projection {
    private int year;
    private double startAmount;
    private double interest;
    private double endAmount;

    public Projection(int year, double startAmount, double interest, double endAmount) {
        this.year = year;
        this.startAmount = startAmount;
        this.interest = interest;
        this.endAmount = endAmount;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public double getStartAmount() {
        return startAmount;
    }

    public void setStartAmount(double startAmount) {
        this.startAmount = startAmount;
    }

    public double getInterest() {
        return interest;
    }

    public void setInterest(double interest) {
        this.interest = interest;
    }

    public double getEndAmount() {
        return endAmount;
    }

    public void setEndAmount(double endAmount) {
        this.endAmount = endAmount;
    }
}
