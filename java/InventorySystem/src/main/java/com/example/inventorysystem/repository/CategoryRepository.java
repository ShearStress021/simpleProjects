package com.example.inventorysystem.repository;

import com.example.inventorysystem.model.Category;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;


import java.util.List;
import java.util.Optional;

public interface CategoryRepository extends JpaRepository<Category,String> {

//    @Query("select c for Category c order by c.catcode")
//    List<Category> findAllOrdered();


    @Query("select c from Category c left  join fetch c.items where c.catcode = :code")
    Optional<Category> findWithItems(@Param("code") String code);


    @Query(value = "select * from category where catdesc like %:kw% order by catcode", nativeQuery = true)
    List<Category> searchByDescription(@Param("kw") String keyword);


    @Query(value = "select count(*) from items where catcode = :code", nativeQuery = true)
    int countItems(@Param("code") String code);

    @Modifying
    @Query(value = "update category set catcode =:newcode, catdesc=:newDesc where catcode=:oldcode",nativeQuery = true)
    int updateCategory(@Param("newcode") String newcode,
                       @Param("oldcode") String oldcode,
                       @Param("newDesc") String newDesc);
}
