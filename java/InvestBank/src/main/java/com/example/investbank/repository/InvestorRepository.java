package com.example.investbank.repository;


import com.example.investbank.model.Investor;
import com.example.investbank.model.SaveType;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.Optional;

public interface InvestorRepository extends JpaRepository<Investor, Long> {


    Optional<Investor> findByCode(String code);

    boolean existsByCode(String code);

    @Query("select sum(i.initialDeposit) from Investor  i")
    Double getInitialDeposit();


    @Query("select sum(i.initialDeposit) from Investor i where i.saveType = :saveType")
    Double getInitialDepositBySaveType(@Param("saveType") SaveType saveType);


}
