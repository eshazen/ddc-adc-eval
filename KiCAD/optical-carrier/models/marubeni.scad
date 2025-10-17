$fn = 32;
mm = 25.4;
e = 0.1;

body_w = 2.7;
body_l = 3.2;
body_h = 1.8;

cone_d2 = 2.4;
cone_d1 = 1.5;
cone_h = 0.9;

module led() {
     difference() {
	  translate( [-body_w/2, -body_l/2, 0])
	       cube( [body_w, body_l, body_h]);
	  translate( [0, 0, body_h-cone_h+e])
	       cylinder( d1=cone_d1, d2=cone_d2, h=cone_h);
	  translate( [body_w/2*0.5, body_l/2, body_h/2])
	       rotate( [0, 0, -45])
	       cube( [10, 10, 10]);
     }
}

led();

