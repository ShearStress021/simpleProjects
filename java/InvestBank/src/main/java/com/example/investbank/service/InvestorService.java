package com.example.investbank.service;

import com.example.investbank.model.Investor;
import com.example.investbank.model.Projection;
import com.example.investbank.model.SaveType;
import com.example.investbank.repository.InvestorRepository;
import jakarta.transaction.Transactional;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
public class InvestorService {
    private final InvestorRepository repo;


    public void saveInvestor(Investor investor) {
        if(repo.existsByCode(investor.getCode())) {
            throw new IllegalArgumentException("Investor with code " + investor.getCode() + " already exists");
        }
        repo.save(investor);
    }
    @Transactional
    public void deleteInvestor(Investor investor) {
        repo.delete(investor);
    }

    @Transactional
    public void updateInvestorInfo(Investor investor) {


        repo.save(investor);
    }

    public List<Investor> findAllInvestors() {
        return repo.findAll();
    }

    public boolean investorExistsByCode(String code) {
        return repo.existsByCode(code);
    }


    public Investor findInvestorById(Long id) {
        return repo.findById(id).orElseThrow(
                () -> new IllegalArgumentException("Investor with id " + id + " not found")
        );
    }


    public  List<Projection> getInvestorProjections(Investor investor) {
        List<Projection> projections = new ArrayList<>();
        int numOfYears = investor.getYears();
        double principal = investor.getInitialDeposit();
        double rate = investor.getSaveType().getRage();

        for(int i=1; i<=numOfYears; i++) {
            double interest = Math.round((principal * rate) * 100.0) / 100.0;
            projections.add(
                    new Projection(
                            i,
                            principal,
                            interest,
                            principal + interest)

                );
            principal += interest;
        }
        return projections;
    }

    public Double calculateTotalInitialDeposit() {
        Double total = repo.getInitialDeposit();
        return total != null ? total : 0.0;
    }

    public Double calculateTotalDepositBySaveTypeRegular() {
        Double total = repo.getInitialDepositBySaveType(SaveType.REGULAR);
        return total != null ? total : 0.0;
    }
    public Double calculateTotalDepositBySaveTypeDeluxer() {
        Double total = repo.getInitialDepositBySaveType(SaveType.DELUXE);
        return total != null ? total : 0.0;
    }


}
