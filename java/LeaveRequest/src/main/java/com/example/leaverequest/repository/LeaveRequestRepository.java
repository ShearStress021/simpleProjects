package com.example.leaverequest.repository;

import com.example.leaverequest.model.LeaveRequest;
import org.springframework.data.jpa.repository.JpaRepository;

public interface LeaveRequestRepository extends JpaRepository<LeaveRequest, Long> {

    int findLeaveDay(LeaveRequest.LeaveType leaveType);
}
