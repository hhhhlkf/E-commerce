package com.linexus.dao;

import com.linexus.pojo.Client;
import com.linexus.pojo.Order;
import com.linexus.pojo.Product;
import com.linexus.pojo.ProductType;
import org.apache.ibatis.annotations.Param;

import javax.jws.WebMethod;
import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-19 - 0:06
 */
@WebService
public interface WholeMapper {
    @WebMethod
    public List<Client> getClientList();
    @WebMethod
    public Client getClientByNameAndPwd(@Param("name") String name, @Param("pwd") String pwd);
    @WebMethod
    public void InsertClient(Client client);
    @WebMethod
    public void deleteClientByNameAndPwd(@Param("name") String name,@Param("pwd") String pwd);
    @WebMethod
    public void updateClient(Client client);
    @WebMethod
    List<Client> getClientLikeList(@Param("mess") String mess);

    //Order
    @WebMethod
    List<Order> getOrderList();

    @WebMethod
    List<Order> getOrderListByInfo(Order order);

    @WebMethod
    void addOrder(Order order);

    @WebMethod
    List<Order> getOrderLikeList(@Param("mess") String mess);

    @WebMethod
    List<Order> getOrderListHistory();
    @WebMethod
    void updateHistory(Order order);

    @WebMethod
    void deleteShoppingCart(Order order);

    //Product
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

    //ProductType
    @WebMethod
    List<ProductType> getProductTypeByProName(@Param("proName") String name);

    @WebMethod
    void addProductType(ProductType type);

    @WebMethod
    void deleteProductTypeByName(@Param("name") String name);
}
