package com.example.myleaveprocesser.repository;


import com.example.myleaveprocesser.model.LeaveModel;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.time.LocalDate;
import java.util.List;

public interface LeaveRepository extends JpaRepository<LeaveModel,Long> {

    @Query("select count(l) > 0 from LeaveModel l " +
            "where l.employeeName = :employeeName " +
            "and l.startDate <= :endDate " +
            "and l.endDate >= :startDate")
    boolean existsOverlappingBooking(@Param("employeeName") String employeeName,
                                     @Param("startDate") LocalDate startDate,
                                     @Param("endDate") LocalDate endDate);

    @Query(value = "SELECT SUM(datediff('DAY',  start_date , end_date)+ 1) FROM leave_model", nativeQuery = true)
    Long findTotalDaysOfAllLeaves();

//    @Query("""
//        SELECT l.leaveType AS type,
//               SUM(DATEDIFF(l.endDate, l.startDate) + 1) AS totalDays
//        FROM LeaveModel l
//        GROUP BY l.leaveType
//    """)
//    List<Object[]> findTotalDaysByLeaveType();
}
