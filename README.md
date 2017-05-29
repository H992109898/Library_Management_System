# Library_Management_System
基于MFC和mySQL的媒体库管理系统

1、问题描述：     

图书馆中的资料很多，如果能分类对其资料流通进行管理，将会带来很多方便，因此需要有一个媒体库管理系统。             

图书馆共有三大类物品资料：图书、视频光盘、图画。                   

这三类物品共同具有的属性有：编号、标题、作者、评级（未评级，一般，成人，儿童)等。其中图书类增加出版社、ISBN号、页数等信息；视频光盘类增加出品者的名字、出品年份和视频时长等信息；图画类增加出品国籍、作品的长和宽（以厘米计，整数）等信息。                   

2．功能要求：    

（1）添加物品：主要完成图书馆三类物品信息的添加，要求编号唯一。当添加了重复的编号时，则提示数据添加重复并取消添加；当物品库已满，则提示不能再添加新的数据。                       

（2）查询物品                     

可按照三种方式来查询物品，分别为：                   

按标题查询：输入标题，输出所查询的信息，若不存在该记录，则提示“该标题不存在！”； 按编号查询：输入编号，输出所查询的信息，若不存在该记录，则提示“该编号不存在！”； 按类别查询：输入类别，输出所查询的信息，若不存在记录，则提示“该类别没有物品！”；               

（3）显示物品库：输出当前物品库中所有物品信息，每条记录占据一行。                          

（4）编辑物品：可根据查询结果对相应的记录进行修改，修改时注意编号的唯一性。                       

（5）删除物品：主要完成图书馆物品信息的删除。如果当前物品库为空，则提示“物品库为空！”，并返回操作；否则，输入要删除的编号，根据编号删除该物品的记录，如果该编号不在物品库中，则提示“该编号不存在”。          

3．其他功能要求：                 

（1）增加图书附带光盘的处理情况，以及电子资源情况的处理（电子资源既可能是图书，又可能是光盘资源）；               

（2）统计信息 输出当前物品库中总物品数，以及按物品类别，统计出当前物品中各类别的物品数并显示。                     

（3）物品存盘：将当前程序中的物品信息存入文件中。                     

（4）读出物品：从文件中将物品信息读入程序。                    

