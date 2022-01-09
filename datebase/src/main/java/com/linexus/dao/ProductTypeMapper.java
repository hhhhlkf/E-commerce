package com.linexus.dao;

import com.linexus.pojo.ProductType;
import org.apache.ibatis.annotations.Param;

import javax.jws.WebMethod;
import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:14
 */
@WebService
public interface ProductTypeMapper {
    @WebMethod
    List<ProductType> getProductTypeByProName(@Param("proName") String name);

    @WebMethod
    void addProductType(ProductType type);

    @WebMethod
    void deleteProductTypeByName(@Param("name") String name);

}
