%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% MC = < Manifold Code >
%%% Copyright (C) 1994-- Michael Holst 
%%%
%%% This library is free software; you can redistribute it and/or 
%%% modify it under the terms of the GNU Lesser General Public 
%%% License as published by the Free Software Foundation; either  
%%% version 2.1 of the License, or (at your option) any later version. 
%%%
%%% This library is distributed in the hope that it will be useful, 
%%% but WITHOUT ANY WARRANTY; without even the implied warranty of 
%%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
%%% Lesser General Public License for more details. 
%%%
%%% You should have received a copy of the GNU Lesser General Public 
%%% License along with this library; if not, write to the Free Software  
%%% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
%%%
%%% rcsid="$Id: mcCube2.m,v 1.3 2010/08/12 05:17:42 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=3;    % intrinsic manifold dimension
    dimii=3;    % imbedding manifold dimension
 vertices=27;    % number of vertices
simplices=48;    % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0    -1.0000000000e+01 -1.0000000000e+01 -1.0000000000e+01
1         0     1.0000000000e+01 -1.0000000000e+01 -1.0000000000e+01
2         0    -1.0000000000e+01  1.0000000000e+01 -1.0000000000e+01
3         0     1.0000000000e+01  1.0000000000e+01 -1.0000000000e+01
4         0    -1.0000000000e+01 -1.0000000000e+01  1.0000000000e+01
5         0     1.0000000000e+01 -1.0000000000e+01  1.0000000000e+01
6         0    -1.0000000000e+01  1.0000000000e+01  1.0000000000e+01
7         0     1.0000000000e+01  1.0000000000e+01  1.0000000000e+01
8         0     0.0000000000e+00  0.0000000000e+00  0.0000000000e+00
9         0    -1.0000000000e+01  0.0000000000e+00 -1.0000000000e+01
10        0     0.0000000000e+00 -1.0000000000e+01  0.0000000000e+00
11        0     0.0000000000e+00  0.0000000000e+00 -1.0000000000e+01
12        0     1.0000000000e+01 -1.0000000000e+01  0.0000000000e+00
13        0     0.0000000000e+00 -1.0000000000e+01 -1.0000000000e+01
14        0     0.0000000000e+00 -1.0000000000e+01  1.0000000000e+01
15        0    -1.0000000000e+01  0.0000000000e+00  0.0000000000e+00
16        0    -1.0000000000e+01 -1.0000000000e+01  0.0000000000e+00
17        0     0.0000000000e+00  1.0000000000e+01 -1.0000000000e+01
18        0     1.0000000000e+01  0.0000000000e+00  0.0000000000e+00
19        0     1.0000000000e+01  0.0000000000e+00 -1.0000000000e+01
20        0     0.0000000000e+00  1.0000000000e+01  0.0000000000e+00
21        0     1.0000000000e+01  0.0000000000e+00  1.0000000000e+01
22        0     1.0000000000e+01  1.0000000000e+01  0.0000000000e+00
23        0    -1.0000000000e+01  1.0000000000e+01  0.0000000000e+00
24        0     0.0000000000e+00  0.0000000000e+00  1.0000000000e+01
25        0     0.0000000000e+00  1.0000000000e+01  1.0000000000e+01
26        0    -1.0000000000e+01  0.0000000000e+00  1.0000000000e+01
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    1    0    0    2 8 9 11
1         0    0    0    1    0    0    5 8 10 14
2         0    0    0    1    0    0    2 8 11 17
3         0    0    0    1    0    0    2 8 17 20
4         0    0    0    1    0    0    2 8 20 23
5         0    0    0    1    0    0    2 8 23 15
6         0    0    0    0    1    0    5 10 8 12
7         0    0    0    1    1    0    0 9 10 13
8         0    0    0    1    0    1    1 11 13 12
9         0    0    1    0    0    0    8 10 13 12
10        0    0    0    0    0    0    13 9 10 8
11        0    0    1    0    0    0    8 9 11 13
12        0    0    0    0    0    0    13 11 8 12
13        0    0    0    0    1    0    2 9 8 15
14        0    0    0    1    1    0    0 10 9 16
15        0    0    0    1    0    1    4 14 16 15
16        0    0    1    0    0    0    8 9 16 15
17        0    0    0    0    0    0    16 10 9 8
18        0    0    1    0    0    0    8 10 14 16
19        0    0    0    0    0    0    16 14 8 15
20        0    0    0    0    1    0    5 12 8 18
21        0    0    0    1    1    0    1 11 12 19
22        0    0    0    1    0    1    3 17 19 18
23        0    0    1    0    0    0    8 12 19 18
24        0    0    0    0    0    0    19 11 12 8
25        0    0    1    0    0    0    8 11 17 19
26        0    0    0    0    0    0    19 17 8 18
27        0    0    0    0    1    0    5 18 8 21
28        0    0    0    1    1    0    3 17 18 22
29        0    0    0    1    0    1    7 20 22 21
30        0    0    1    0    0    0    8 18 22 21
31        0    0    0    0    0    0    22 17 18 8
32        0    0    1    0    0    0    8 17 20 22
33        0    0    0    0    0    0    22 20 8 21
34        0    0    0    0    1    0    5 21 8 24
35        0    0    0    1    1    0    7 20 21 25
36        0    0    0    1    0    1    6 23 25 24
37        0    0    1    0    0    0    8 21 25 24
38        0    0    0    0    0    0    25 20 21 8
39        0    0    1    0    0    0    8 20 23 25
40        0    0    0    0    0    0    25 23 8 24
41        0    0    0    0    1    0    5 24 8 14
42        0    0    0    1    1    0    6 23 24 26
43        0    0    0    1    0    1    4 15 26 14
44        0    0    1    0    0    0    8 24 26 14
45        0    0    0    0    0    0    26 23 24 8
46        0    0    1    0    0    0    8 23 15 26
47        0    0    0    0    0    0    26 15 8 14
];

mcsf_end=1;

