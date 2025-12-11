package com.example.investbank.model;

public enum SaveType {
    REGULAR, DELUXE;

    public double getRage(){
        return switch (this) {
            case REGULAR -> 0.15;
            case DELUXE -> 0.1;
            default -> 0.0;
        };
    }


}
