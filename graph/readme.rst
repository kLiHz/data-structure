.. _header-n286:

Graph
=====

.. _header-n289:

图的基本概念
------------

图是一种数据结构，由\ **顶点**\ 集合和\ **顶点间关系**\ 的集合组成，定义为：\ |image1|\ 。\ |image2|\ 是一个非空有限集合，代表顶点（结点），\ |image3|\ 代表边的集合。

有向图：图的边有方向，只能按箭头方向从一点到另一点。\ |image4|

无向图：图的边没有方向。\ |image5|

邻接顶点：如果\ :math:`(u, v)`\ 是\ :math:`E(G)`\ 中的一条边，则称\ :math:`u`\ 与\ :math:`v`\ 互为邻接顶点。

结点的度：无向图中与结点相连的边的数目，称为结点的度。

结点的入度：在有向图中，以这个结点为终点的有向边的数目。

结点的出度：在有向图中，以这个结点为起点的有向边的数目。

权值：边的“费用”，可以形象地理解为边的长度。

连通：如果图中结点\ :math:`u`\ 、\ :math:`v`\ 之间存在一条从\ :math:`u`\ 通过若干条边、点到达\ :math:`v`\ 的通路，则称\ :math:`u`\ 、\ :math:`v`\ 是连通的。

回路：起点和终点相同的路径，称为回路，或“环”。

完全图：一个\ :math:`n`\ 阶的完全无向图有\ :math:`\frac{1}{2}n(n-1)`\ 条边；一个\ :math:`n`\ 阶的完全有向图有\ :math:`n(n-1)`\ 条边。

稠密图：一个边数接近完全图的图。

稀疏图：一个边数远远少于完全图的图。

子图：设有两个图\ :math:`G=(V,E)`\ 和\ :math:`G'=(V',E')`\ 。若\ |image6|\ 且\ |image7|\ ，则称图\ :math:`G'`\ 是图\ :math:`G`\ 的子图。

连通图：如果图中任意两点都是连通的，则称此图是连通图。

连通分量：非连通图的极大连通子图叫做连通分量。

强连通图：在有向图中，若对于每一对顶点\ :math:`v_i`\ 和\ :math:`v_j`\ ，都存在一条从\ :math:`v_i`\ 到\ :math:`v_j`\ 和\ :math:`v_j`\ 到\ :math:`v_i`\ 的路径，则称此图是强连通图。

强连通分量：非强连通图的极大强连通子图。特殊地，单个点也算一个强连通分量。

生成树

.. _header-n310:

图的存储
--------

.. |image1| image:: https://render.githubusercontent.com/render/math?math=Graph=(V,E)
.. |image2| image:: https://render.githubusercontent.com/render/math?math=V
.. |image3| image:: https://render.githubusercontent.com/render/math?math=E
.. |image4| image:: https://render.githubusercontent.com/render/math?math=E=\{\langle x,y\rangle | x,y \in V\}
.. |image5| image:: https://render.githubusercontent.com/render/math?math=E=\{(x,y) | x,y \in V\}
.. |image6| image:: https://render.githubusercontent.com/render/math?math=V'\subseteq V
.. |image7| image:: https://render.githubusercontent.com/render/math?math=E'\subseteq E
