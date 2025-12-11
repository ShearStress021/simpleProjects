package com.example.leaverequest.model;


import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Date;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class LeaveRequest {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String EmployeeName;

    @Column(nullable = false)
    @Enumerated(EnumType.STRING)
    private LeaveType leaveType;



    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;


    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;


    private String reason;


    public long getDaysBetween() {
        return ChronoUnit.DAYS.between(startDate, endDate);
    }



    public enum LeaveType {
        VACATION,EMERGENCY,SICK_LEAVE;
        public static LeaveType fromString(String s){
            if (s == null)
                return null;
            for (LeaveType leaveType : LeaveType.values()) {
                if (leaveType.name().equalsIgnoreCase(s.trim())) {
                    return leaveType;
                }
            }
            return null;
        };

    }
}
