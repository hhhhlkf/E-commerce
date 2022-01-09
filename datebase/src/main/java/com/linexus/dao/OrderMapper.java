package com.linexus.dao;

import com.linexus.pojo.Order;
import org.apache.ibatis.annotations.Param;

import javax.jws.WebMethod;
import javax.jws.WebService;
import java.util.List;
import java.util.Map;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:13
 */
@WebService
public interface OrderMapper {
    @WebMethod
    public List<Order> getOrderList();

    @WebMethod
    public List<Order> getOrderListByInfo(Order order);

    @WebMethod
    public void addOrder(Order order);

    @WebMethod
    List<Order> getOrderLikeList(@Param("mess") String mess);

    @WebMethod
    List<Order> getOrderListHistory();
    @WebMethod
    void updateHistory(Order order);

    @WebMethod
    void deleteShoppingCart(Order order);
}
