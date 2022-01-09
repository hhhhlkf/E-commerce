package com.linexus.dao;

import com.linexus.pojo.Product;
import org.apache.ibatis.annotations.Param;

import javax.jws.WebMethod;
import javax.jws.WebService;
import java.util.List;
import java.util.Map;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:14
 */
@WebService
public interface ProductMapper {
    @WebMethod
    List<Product>  getProductList(@Param("choose") int choose);
    @WebMethod
    List<Product>  getProductListByInfo(Product product);
    @WebMethod
    void addProduct(Product product);
    @WebMethod
    void deleteProductByInfo(Product product);
    @WebMethod
    void updateProductByInfo(Product product);
    @WebMethod
    List<Product> getProductLikeList(@Param("mess") String mess);
}
