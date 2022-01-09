import com.linexus.dao.*;
import com.linexus.pojo.Client;
import com.linexus.pojo.Order;
import com.linexus.pojo.Product;
import com.linexus.pojo.ProductType;
import org.apache.ibatis.annotations.Mapper;
import org.junit.Test;
import org.junit.validator.PublicClassValidator;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import java.math.BigDecimal;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.function.BiFunction;

/**
 * @author hhhhlkf
 * @date 2021-12-16 - 12:55
 */
public class myTest {
    @Test
    public void Test1() {
        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        WholeMapper mapper = (WholeMapper) context.getBean("WholeMapper");
//        查找全部的Client
//        List<Client> clientList = mapper.getClientList();
//        for (Client client : clientList) {
//            System.out.println(client);
//        }
////        模糊查找
//        List<Client> likeList = mapper.getClientLikeList("吴");
//        for (Client client : likeList) {
//            System.out.println(client);
//        }
////        查找指定的人
//        Client client1 = mapper.getClientByNameAndPwd("吴国梁", "123456789");
//        System.out.println(client1);
//        新建人
        Client client = new Client();
//        client.setClientBought(0);
        client.setClientName("你爸爸");
        client.setClientPwd("123456789");
//        System.out.println(client.getClientId());
//        mapper.InsertClient(client);
//        删除指定的人
//        mapper.deleteClientByNameAndPwd("你好", "123456789");
        mapper.updateClient(client);
    }

    @Test
    public void Test2() {

        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        WholeMapper mapper = (WholeMapper) context.getBean("WholeMapper");
        //查询所有的order
//        Order order2 = new Order();
//        order2.setOrderClientId(3);
//        List<Order> orderList1 = mapper.getOrderListByInfo(order2);
//        for (Order order : orderList1) {
//            System.out.println(order);
//        }
//        List<Order> orderList = mapper.getOrderList();
//        for (Order order : orderList) {
//            System.out.println(order);
//        }
//        //添加东西
        Order order = new Order();
        order.setOrderClient("吴国梁");
        String money = new String("1330.00");
        BigDecimal bigDecimal = new BigDecimal(money);
        order.setOrderCost(bigDecimal);
        order.setOrderClientId(3);
        order.setOrderProductName("柯西高达");
        order.setOrderProductNum(3);
        order.setOrderProductId(1);
        order.setOrderTime(new Date(121, Calendar.NOVEMBER,13));
        order.setOrderProductStyle("normal");
        order.setOrderCheck(1);
        order.setOrderHide(-1);
        mapper.addOrder(order);
//        order.setOrderId(10);
//        List<Order> orders = mapper.getOrderListByInfo(order);
//        for (Order order1 : orders) {
//            System.out.println(order1);
//        }
//        mapper.getOrderLikeList("l");
//        Order order = new Order();
//        order.setOrderCheck(-1);
//        order.setOrderId(3);
//        order.setOrderHide(1);
//        order.setOrderCheck(-1);
//        mapper.updateHistory(order);
//        mapper.deleteShoppingCart(order);
//        Order order = new Order();
//        order.setOrderClientId(3);
//        order.setOrderHide(-1);
//        order.setOrderCheck(1);
//        List<Order> orderList = mapper.getOrderListByInfo(order);
//        for (Order order1 : orderList) {
//            System.out.println(order1);
//        }
    }

    @Test
    public void Test3() {
        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        WholeMapper mapper = (WholeMapper) context.getBean("WholeMapper");
//        List<Product> productList = mapper.getProductList(2);
//        for (Product product : productList) {
//            System.out.println(product);
//        }
        Product product = new Product();
        product.setProductName("火焰金刚");
        mapper.deleteProductByInfo(product);
//        product.setProductName("垃圾的高达");
//        product.setProductPrice(251);
//        product.setProductBuyNum(4);
//        product.setProductNum(40);
//        product.setProductImage("D:/code/Qt/C++project/imagebase/夏亚高达.jpg");
//        product.setProductDiscount((float) 0.5);
//        //mapper.addProduct(product);
//        product.setProductId(15);
////        List<Product> products = mapper.getProductListByInfo(product);
////        for (Product product1 : products) {
////            System.out.println(product1);
////        }
//        mapper.updateProductByInfo(product);
//
//        List<Product> products = mapper.getProductLikeList("绿");
//        for (Product product1 : products) {
//            System.out.println(product1);
//        }
    }

    @Test
    public void Test4()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        ProductTypeMapper mapper = (ProductTypeMapper) context.getBean("ProductTypeMapper");
        List<ProductType> typeList = mapper.getProductTypeByProName("扎古");
        for (ProductType productType : typeList) {
            System.out.println(productType);
        }
    }

    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("spring-config.xml");
        System.out.println("服务发布成功！");
    }
}
