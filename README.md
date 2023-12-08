# GPU Collision Detection

Computer Animation Project

`CMakeLists.txt` from [Glitter](http://polytonic.github.io/Glitter/)



## 算法概述

朴素的算法会将 $n$ 个物体中的每一个物体与其他 $n-1$ 个物体进行碰撞检测，其时间复杂度为 $O(n^2)$。


此项目使用的数据结构是层级包围体树。一个包围体必需包含它的物体的所有点。为了加快计算，通常会使用最小轴对齐包围盒（minimum axis-aligned bounding box），即最小的，各个边与三个坐标轴平行的长方体。
包围体可以形成树结构，约束条件是叶节点必须是物体本身，而所有其他节点都是包围体，并且任意一个内部节点必须是它的子节点的包围盒。
在便利层级包围体树时，若一个物体与某一个节点表示的包围体没有碰撞，则物体不会与此包围体的子包围体/物体碰撞，因此可以跳过子节点。对于理想构建的树而言，时间复杂度可以降低到 $O(n\log n)$。

## 树的构建

目前存在[https://web.archive.org/web/20140113213158/http://visual-computing.intel-research.net/publications/papers/2008/async/AsyncBVHJournal2008.pdf](高效的算法)，可以