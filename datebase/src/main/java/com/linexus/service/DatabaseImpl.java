package com.linexus.service;

import com.linexus.dao.ClientMapper;
import com.linexus.dao.OrderMapper;
import com.linexus.dao.ProductMapper;
import com.linexus.dao.ProductTypeMapper;
import com.linexus.pojo.Client;
import com.linexus.pojo.Order;
import com.linexus.pojo.Product;
import com.linexus.pojo.ProductType;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 9:12
 */

@WebService(serviceName = "Database")
public class DatabaseImpl extends SqlSessionDaoSupport implements OrderMapper, ClientMapper, ProductMapper, ProductTypeMapper {
    @Override
    public List<Client> getClientList() {
        return getSqlSession().getMapper(ClientMapper.class).getClientList();
    }

    @Override
    public Client getClientByNameAndPwd(String name, String pwd) {
        return getSqlSession().getMapper(ClientMapper.class).getClientByNameAndPwd(name,pwd);
    }

    @Override
    public void InsertClient(Client client) {
        getSqlSession().getMapper(ClientMapper.class).InsertClient(client);
    }

    @Override
    public void deleteClientByNameAndPwd(String name, String pwd) {
        getSqlSession().getMapper(ClientMapper.class).deleteClientByNameAndPwd(name,pwd);
    }

    @Override
    public void updateClient(Client client) {
        getSqlSession().getMapper(ClientMapper.class).updateClient(client);
    }

    @Override
    public List<Client> getClientLikeList(String mess) {
        return getSqlSession().getMapper(ClientMapper.class).getClientLikeList(mess);
    }

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

    @Override
    public List<Product> getProductList(int choose) {
        return getSqlSession().getMapper(ProductMapper.class).getProductList(choose);
    }

    @Override
    public List<Product> getProductListByInfo(Product product) {
        return getSqlSession().getMapper(ProductMapper.class).getProductListByInfo(product);
    }
    @Override
    public void addProduct(Product product) {
        getSqlSession().getMapper(ProductMapper.class).addProduct(product);
    }

    @Override
    public void deleteProductByInfo(Product product) {
        getSqlSession().getMapper(ProductMapper.class).deleteProductByInfo(product);
    }

    @Override
    public void updateProductByInfo(Product product) {
        getSqlSession().getMapper(ProductMapper.class).updateProductByInfo(product);
    }

    @Override
    public List<Product> getProductLikeList(String mess) {
        return getSqlSession().getMapper(ProductMapper.class).getProductLikeList(mess);
    }


    @Override
    public List<ProductType> getProductTypeByProName(String name) {
        return getSqlSession().getMapper(ProductTypeMapper.class).getProductTypeByProName(name);
    }

    @Override
    public void addProductType(ProductType type) {
        getSqlSession().getMapper(ProductTypeMapper.class).addProductType(type);
    }

    @Override
    public void deleteProductTypeByName(String name) {
        getSqlSession().getMapper(ProductTypeMapper.class).deleteProductTypeByName(name);
    }
}
