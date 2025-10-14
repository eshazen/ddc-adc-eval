//
// car computer enclosure
//

mm = 25.4;
$fn = 32;
e = 0.1;

include <oled.scad>

//
// case body
//
// body_spc = 0.05*mm;
body_spc = 0.075*mm;

body_w = 6.875*mm-body_spc;
body_h = 2.125*mm-body_spc;

//--- normal
//body_d = 2.5*mm;
//pcb_standoff_down = 0.25*mm + 0.7*mm;
//--- fast print
body_d = 10;     /* fast print */
pcb_standoff_down = 2;

body_thk = 1.6;
body_lip = 2.0;

panel_w = body_w + 2*body_lip;
panel_h = body_h + 2*body_lip;

panel_w_in = body_w-2*body_thk;
panel_h_in = body_h-2*body_thk;

// PCB mounting holes
pcb_hole_dx = 6.25*mm;
pcb_hole_dy = 1.5*mm;
// pcb_hole_dia = 0.098*mm;	/* 4-40 tap drill */
pcb_hole_dia = 0.140*mm;	/* 6-32 test fit */
pcb_standoff_dia = 0.25*mm;


panel_hole_dia = 0.15*mm;

pcb_so_supp_wid = 3;
pcb_so_supp_len = pcb_hole_dia/2+6-body_spc/2;

module standoff_at( x, y, dia, hole, hgt, rot) {
    translate( [x, y, 0]) {
      rotate( [0, 0, rot]) {
      difference() {
	union() {
	  cylinder( d=dia, h=hgt);
	  translate( [-pcb_so_supp_wid/2, -pcb_so_supp_len, 0])
	    cube( [pcb_so_supp_wid, pcb_so_supp_len, hgt]);
	}
	translate( [0, 0, -e])
	  cylinder( d=hole, h=hgt+2*e);
      }
    }
  }
}

// draw box with lip, centered
module box() {
     translate( [-body_w/2, -body_h/2, -body_d])
     difference() {
	  union() {
	       // box body
	       cube( [body_w, body_h, body_d]);
	       // lip
	       translate( [-body_lip, -body_lip, body_d-body_thk])
		    cube( [body_w+2*body_lip, body_h+2*body_lip, body_thk]);
	  }
	  // cavity
	  translate( [body_thk, body_thk, body_thk])
	       cube( [body_w-2*body_thk, body_h-2*body_thk, body_d]);
	  // wiring hole
	  translate( [4*body_w/5, body_h/2, -e])
	       cylinder( d=0.375*mm, h=10);
	  echo("Cavity (mm)", body_w-2*body_thk, body_h-2*body_thk, body_d);
	  echo("Cavity (in)", (body_w-2*body_thk)/mm, (body_h-2*body_thk)/mm, body_d/mm);
     }

     translate( [0, 0, -body_d+body_thk-e]) {
       standoff_at( -pcb_hole_dx/2, -pcb_hole_dy/2, pcb_standoff_dia, pcb_hole_dia, body_d-pcb_standoff_down, 270); 
       standoff_at( -pcb_hole_dx/2, pcb_hole_dy/2, pcb_standoff_dia, pcb_hole_dia, body_d-pcb_standoff_down, 270);
       standoff_at( pcb_hole_dx/2, -pcb_hole_dy/2, pcb_standoff_dia, pcb_hole_dia, body_d-pcb_standoff_down, 90); 
       standoff_at( pcb_hole_dx/2, pcb_hole_dy/2, pcb_standoff_dia, pcb_hole_dia, body_d-pcb_standoff_down, 90);
    }
}

module mounting_holes() {
  translate( [-pcb_hole_dx/2, -pcb_hole_dy/2, 0]) cylinder( h=20, d=panel_hole_dia);
  translate( [-pcb_hole_dx/2, pcb_hole_dy/2,  0]) cylinder( h=20, d=panel_hole_dia);
  translate( [pcb_hole_dx/2, -pcb_hole_dy/2,  0]) cylinder( h=20, d=panel_hole_dia);
  translate( [pcb_hole_dx/2, pcb_hole_dy/2, 0]) cylinder( h=20, d=panel_hole_dia);
}


// front panel, centered

module panel() {
  translate( [-panel_w/2, -panel_h/2, 0]) {
    cube( [panel_w, panel_h, body_thk]);
    translate( [body_lip+body_thk, body_lip+body_thk, -body_thk+e])
      cube( [panel_w_in, panel_h_in, body_thk]);
  }
     
}

// holes for switches, knob, LEDs, USB
module button_holes() {
  // LEDs
  translate( [-115, 35, 0])  
    cylinder( d=3.5, h=20);
  translate( [-108, 35, 0])  
    cylinder( d=3.5, h=20);
  // knob
  translate( [-114, 18.5, 0])
    cylinder( d=17, h=20);
  // left 2 switches
  cube( [18, 38, 20]);
  // USB
  translate( [12.7, -6.5, 0])
    cube( [12, 5, 20]);
}

// translate( [0,0,16]) {
//   difference() {
//     panel();
//     translate( [0, 0, -5]) {
//       translate( [-9,2,0]) oled_holes();
//       mounting_holes();
//       translate( [42.7, -16, 0])
//       button_holes();
//       translate( [panel_w/2-14, 0, 0]) cylinder( h=20, d=0.26*mm);
//     }
//   }
// }


box();

// translate( [0, 0, 5]) {
//      difference() {
//        	  color("brown") panel();
// 	  translate( [-body_w+0.65*mm, 70, 0])
// 	       translate( [147.5, -69.7, 0]) oled_holes();
//      }
// }
// 
// 

// translate( [-body_w+0.62*mm, 71.8, 10]) {
//       color("green") import("car-control.stl");
//       translate( [147.5, -69.9, 3]) oled();
// }
