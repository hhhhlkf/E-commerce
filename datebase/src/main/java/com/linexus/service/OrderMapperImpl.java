package com.linexus.service;

import com.linexus.dao.OrderMapper;
import com.linexus.pojo.Order;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 10:29
 */
@WebService(serviceName = "OrderMapper")
public class OrderMapperImpl extends SqlSessionDaoSupport implements OrderMapper {

    @Override
    public List<Order> getOrderList() {
        return getSqlSession().getMapper(OrderMapper.class).getOrderList();
    }

    @Override
    public List<Order> getOrderListByInfo(Order order) {
        return getSqlSession().getMapper(OrderMapper.class).getOrderListByInfo(order);
    }

    @Override
    public void addOrder(Order order) {
        getSqlSession().getMapper(OrderMapper.class).addOrder(order);
    }

    @Override
    public List<Order> getOrderLikeList(String mess) {
        return getSqlSession().getMapper(OrderMapper.class).getOrderLikeList(mess);

    }

    @Override
    public List<Order> getOrderListHistory() {
        return getSqlSession().getMapper(OrderMapper.class).getOrderListHistory();
    }

    @Override
    public void updateHistory(Order order) {
        getSqlSession().getMapper(OrderMapper.class).updateHistory(order);
    }

    @Override
    public void deleteShoppingCart(Order order) {
        getSqlSession().getMapper(OrderMapper.class).deleteShoppingCart(order);
    }
}
