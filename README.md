# Mysql Automatically build grammar

如名字所示：mysql语句自动构建工具

因为近期从事大量繁琐的数据分析工作，为了方便自己也方便其他人，写了这么个潦草的工具。代码很简单，实现也非常容易，会持续更新。

Using：

```shell
mabg select username,amount from `xxx_201801` -r 201801 -s 201801 -e 202002
or
mabg select username,amount from `xxx_20180101` -r 20180101 -s 20180101 -e 20200201
```

Result:

![image-20201208221623088](/image/image-20201208221623088.png)
