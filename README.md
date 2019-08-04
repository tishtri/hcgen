# hcgen

Generator of hypercube Petri net models with various edge conditions


Description:
------------

A cell of hypercube grid represents a packet switching device with ports situated on facets of the unit-sized hypercube. A device works in full-duplex mode using store-and-forward principle with limited capacity of buffer. Neighboring cells are connected via merging contact places situated on common facets according to von Neumann neigborhood. Four edge conditions are implemented: open grid with hanging contact places; closed opposite edges -- hypertorus; plug devices on edges connecting output channel of the edge port with its input channel; truncated devices without edge ports, corresponding sections of internal buffer, and incidental transitions of other ports.


Command line format:
--------------------

>hcgen e d k p b > ht_model.net


Parameters:
-----------

e   edge condition: 'o' - open, 't' - torus, 'r' - truncated device, 'g' - plug device,

d   the number of dimensions;

k   the hypercube size, actually k x k x k x ... x k - d times;

p   the number of packets in each section of the internal buffer;

b   the internal buffer available size.


Output (file) format:
---------------------

.net  Time Petri nets textual format according to http://www.laas.fr/tina


Tools to display, edit, visualize, and analyze generated models:
----------------------------------------------------------------

Tina Toolbox for analysis of Petri nets and Time Petri nets http://www.laas.fr/tina

Exported from Tina models are opened with other tools for Petri nets http://www.informatik.uni-hamburg.de/TGI/PetriNets/tools/quick.html


An example:
-----------

>hcgen r 2 3 2 3 > hcr2d3k2p3b.net

- Generate a model of a hypercube with 2 dimensions of size 3 with 2 packets in each buffer section and 
available size of buffer 3 with truncated switching devices on edges.

>nd hcr2d3k2p3b.net

- Load the model into graphical environment of Tina. 

Menue: "Edit - draw - nearto"

- Visualize the model. 

Menue: "Tools - stepper simulator - Rand"

- Watch the token game.

Examples of automatically visualized nets for 2D case and various edge conditions are saved in the following files: hco2d3k2p3b.pdf -- open, hct2d3k2p3b.pdf -- closed (torus), hcg2d3k2p3b.pdf -- plug devices, hcr2d3k2p3b.pdf -- truncated devices.

Automatic visualization for higher number of dimensions is not of much use.


References:
-----------

Dmitry A. Zaitsev, Ivan D. Zaitsev and Tatiana R. Shmeleva. Infinite Petri Nets: Part 2, Modeling Triangular, Hexagonal, Hypercube and Hypertorus Structures, Complex Systems, 26(4), 2017, 341-371. DOI: 10.25088/ComplexSystems.26.2.341

Dmitry A. Zaitsev, Ivan D. Zaitsev and Tatiana R. Shmeleva. Infinite Petri Nets: Part 1, Modeling Square Grid Structures, Complex Systems, 26(2), 2017, 157-195. DOI: 10.25088/ComplexSystems.26.2.157 

Dmitry A. Zaitsev Generator of hypertorus Petri net models, 2015, https://github.com/dazeorgacm/htgen


---------------------------
    tishtri@rambler.ru
---------------------------

