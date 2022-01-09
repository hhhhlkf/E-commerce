package com.linexus.service;

import com.linexus.dao.OrderMapper;
import com.linexus.dao.ProductMapper;
import com.linexus.dao.ProductTypeMapper;
import com.linexus.pojo.Product;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import javax.jws.WebService;
import java.util.List;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 10:29
 */
@WebService(serviceName = "ProductMapper")
public class ProductMapperImpl extends SqlSessionDaoSupport implements ProductMapper {

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
}
