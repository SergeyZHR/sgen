#define OUT (*params.out)  \
 \

/*5:*/
#line 332 "./pp3.w"

#include <iostream> 
#include <cstring> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <map> 
#include <list> 
#include <iomanip> 
#include <cstdlib> 
#include <cmath> 
#include <cfloat> 

using namespace std;

/*43:*/
#line 1686 "./pp3.w"

inline double my_fmin(const double&x,const double&y){
return x<y?x:y;
}

inline double my_fmax(const double&x,const double&y){
return x> y?x:y;
}

inline double my_fdim(const double&x,const double&y){
return x> y?x-y:0.0;
}


/*:43*/
#line 347 "./pp3.w"


/*:5*//*7:*/
#line 369 "./pp3.w"

const char*pp3data_env_raw= getenv("PP3DATA");
const string pp3data_env= (pp3data_env_raw==NULL?
"":pp3data_env_raw);
#ifdef PP3DATA
const string pp3data(PP3DATA);
#else
const string pp3data;
#endif
const string filename_prefix(!pp3data_env.empty()?
pp3data_env+'/':(pp3data.empty()?
"":pp3data+"/"));


/*:7*//*8:*/
#line 385 "./pp3.w"

/*70:*/
#line 2401 "./pp3.w"

struct color{
double red,green,blue;
string name;
color(string name,double red,double green,double blue)
:red(red),green(green),blue(blue),name(name){}
color(double red,double green,double blue)
:red(red),green(green),blue(blue),name(){}
void set(ostream&out)const;
};

/*:70*/
#line 386 "./pp3.w"


struct parameters{
double center_rectascension,center_declination;
double view_frame_width,view_frame_height;
double grad_per_cm;
double label_skip,minimal_nebula_radius,faintest_cluster_magnitude,
faintest_diffuse_nebula_magnitude,faintest_star_magnitude,
star_scaling,minimal_star_radius,faintest_star_disk_magnitude,
faintest_star_with_label_magnitude,shortest_constellation_line;
string constellation;
int font_size;
double penalties_label,penalties_star,penalties_nebula,
penalties_boundary,penalties_boundary_rim,penalties_cline,
penalties_cline_rim,penalties_threshold,penalties_rim;
string filename_stars,filename_nebulae,filename_dimensions,
filename_lines,filename_boundaries,filename_milkyway,
filename_preamble,filename_include;
string filename_output;
ostream*out;
istream*in;
bool input_file;
color bgcolor,gridcolor,eclipticcolor,horizoncolor,boundarycolor,hlboundarycolor,
starcolor,nebulacolor,labelcolor,textlabelcolor,clinecolor,
milkywaycolor;
double linewidth_grid,linewidth_ecliptic,linewidth_horizon,linewidth_boundary,
linewidth_hlboundary,linewidth_cline,linewidth_nebula;
string linestyle_grid,linestyle_ecliptic,linestyle_horizon,linestyle_boundary,
linestyle_hlboundary,linestyle_cline,linestyle_nebula;
bool milkyway_visible,nebulae_visible,colored_stars,show_grid,
show_ecliptic,show_horizon,show_boundaries,show_lines,show_labels;
bool create_eps,create_pdf;
parameters():/*9:*/
#line 427 "./pp3.w"

center_rectascension(5.8),center_declination(0.0),
view_frame_width(15.0),view_frame_height(15.0),
grad_per_cm(4.0),
constellation("ORI"),font_size(10),
label_skip(0.06),minimal_nebula_radius(0.1),
faintest_cluster_magnitude(4.0),
faintest_diffuse_nebula_magnitude(8.0),
faintest_star_magnitude(7.0),star_scaling(1.0),
minimal_star_radius(0.015),
faintest_star_disk_magnitude(4.5),
faintest_star_with_label_magnitude(3.7),
shortest_constellation_line(0.1),
penalties_label(1.0),penalties_star(1.0),
penalties_nebula(1.0),penalties_boundary(1.0),
penalties_boundary_rim(1.0),penalties_cline(1.0),
penalties_cline_rim(1.0),penalties_threshold(1.0),
penalties_rim(1.0),
filename_stars(filename_prefix+"stars.dat"),
filename_nebulae(filename_prefix+"nebulae.dat"),
filename_dimensions("labeldimens.dat"),
filename_lines(filename_prefix+"lines.dat"),
filename_boundaries(filename_prefix+"boundaries.dat"),
filename_milkyway(filename_prefix+"milkyway.dat"),
filename_preamble(),filename_include(),
filename_output(),out(&cout),in(0),input_file(false),
bgcolor("bgcolor",0,0,0.4),
gridcolor("gridcolor",0,0.298,0.447),
eclipticcolor("eclipticcolor",1,0,0),
horizoncolor("horizoncolor",0,1,0.5),
boundarycolor("boundarycolor",0.5,0.5,0),
hlboundarycolor("hlboundarycolor",1,1,0),
starcolor("starcolor",1,1,1),
nebulacolor("nebulacolor",1,1,1),
labelcolor("labelcolor",0,1,1),
textlabelcolor(1,1,0),
clinecolor("clinecolor",0,1,0),
milkywaycolor(0,0,1),
linewidth_grid(0.025),linewidth_ecliptic(0.018),linewidth_horizon(0.018),
linewidth_boundary(0.035),linewidth_hlboundary(0.035),
linewidth_cline(0.035),linewidth_nebula(0.018),
linestyle_grid("solid"),linestyle_ecliptic("dashed"),linestyle_horizon("solid"),
linestyle_boundary("dashed"),
linestyle_hlboundary("dashed"),linestyle_cline("solid"),
linestyle_nebula("solid"),
milkyway_visible(false),
nebulae_visible(true),
colored_stars(true),
show_grid(true),show_ecliptic(true),show_horizon(true),show_boundaries(true),
show_lines(true),show_labels(true),
create_eps(false),
create_pdf(false)


/*:9*/
#line 418 "./pp3.w"
{}
int view_frame_width_in_bp(){
return int(ceil(view_frame_width/2.54*72));
}
int view_frame_height_in_bp(){
return int(ceil(view_frame_height/2.54*72));
}
}params;

/*:8*//*39:*/
#line 1589 "./pp3.w"

typedef enum{hidden,visible,undecided}visibility;

struct view_data{
visibility in_view;
double x,y;
double radius,skip;
visibility with_label;
bool label_arranged;
string label;
double label_width,label_height,label_depth;
bool on_baseline;
color label_color;
int label_angle;
view_data():in_view(undecided),x(DBL_MAX),y(DBL_MAX),radius(0.0),
skip(params.label_skip),
with_label(undecided),label_arranged(false),label(),
label_width(0.0),label_height(0.0),
label_depth(0.0),on_baseline(false),
label_color(params.labelcolor),label_angle(0){}
void get_label_boundaries(double&left,double&right,double&top,
double&bottom)const;
double scope()const{return radius+skip+
my_fmax(label_width,label_height)+2.0*skip;}
bool has_valid_coordinates()const{return x!=DBL_MAX&&y!=DBL_MAX;}
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

/*:39*//*40:*/
#line 1623 "./pp3.w"

typedef vector<view_data*> objects_list;

/*:40*//*41:*/
#line 1635 "./pp3.w"

void view_data::get_label_boundaries(double&left,double&right,double&top,
double&bottom)const{
const double origin_x= 
x+(radius+skip)*cos(M_PI_4*double(label_angle));
const double origin_y= 
y+(radius+skip)*sin(M_PI_4*double(label_angle));
switch(label_angle){
case 0:case 1:case 7:left= origin_x;break;
case 2:case 6:left= origin_x-label_width/2.0;break;
case 3:case 4:case 5:left= origin_x-label_width;break;
}
right= left+label_width;
switch(label_angle){
case 0:case 4:bottom= origin_y-
(on_baseline?0.0:label_height/2.0);break;
case 1:case 2:case 3:bottom= origin_y;break;
case 5:case 6:case 7:bottom= origin_y-label_height;break;
}
if(on_baseline)bottom-= label_depth;
top= bottom+label_height;
}

/*:41*//*42:*/
#line 1663 "./pp3.w"

double view_data::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)const{
if(with_label==visible&&label_arranged){
double left2,right2,top2,bottom2;
get_label_boundaries(left2,right2,top2,bottom2);
const double overlap_left= my_fmax(left,left2);
const double overlap_right= my_fmin(right,right2);
const double overlap_top= my_fmin(top,top2);
const double overlap_bottom= my_fmax(bottom,bottom2);
const double overlap_x= my_fdim(overlap_right,overlap_left);
const double overlap_y= my_fdim(overlap_top,overlap_bottom);
return overlap_x*overlap_y*params.penalties_label;
}else return 0.0;
}

/*:42*//*44:*/
#line 1716 "./pp3.w"

struct star:public view_data{
int hd,bs;
double rectascension,declination;
double magnitude;
double b_v;
int flamsteed;
string name;
string constellation;
string spectral_class;
star():hd(0),bs(0),rectascension(0.0),declination(0.0),
magnitude(0.0),b_v(0.0),flamsteed(0),name(""),
spectral_class(""),view_data(){}
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

/*:44*//*45:*/
#line 1740 "./pp3.w"

double star::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)const{
double penalties= view_data::penalties_with(left,right,top,bottom,
core);
const double left2= x-radius,right2= x+radius,top2= y+radius,
bottom2= y-radius;
const double overlap_left= my_fmax(left,left2);
const double overlap_right= my_fmin(right,right2);
const double overlap_top= my_fmin(top,top2);
const double overlap_bottom= my_fmax(bottom,bottom2);
const double overlap_x= my_fdim(overlap_right,overlap_left);
const double overlap_y= my_fdim(overlap_top,overlap_bottom);
penalties+= overlap_x*overlap_y*params.penalties_star;
return penalties;
}


typedef vector<star> stars_list;

/*:45*//*46:*/
#line 1783 "./pp3.w"

istream&operator>>(istream&in,star&s){
in>>s.hd>>s.bs>>s.rectascension
>>s.declination>>s.magnitude>>s.b_v
>>s.flamsteed;
char ch;
do in.get(ch);while(in&&ch!='\n');
getline(in,s.name);
getline(in,s.constellation);
getline(in,s.spectral_class);
return in;
}

/*:46*//*47:*/
#line 1799 "./pp3.w"

void read_stars(stars_list&stars){
ifstream stars_file(params.filename_stars.c_str());
if(!stars_file)throw string("No stars file found: "
+params.filename_stars);
star current_star;
stars_file>>current_star;
while(stars_file){
current_star.label= string("\\Starname{")+current_star.name+'}';
stars.push_back(current_star);
stars_file>>current_star;
}
}


/*:47*//*48:*/
#line 1818 "./pp3.w"

typedef enum{unknown,galaxy,emission,reflection,open_cluster,
globular_cluster}nebula_kind;

/*:48*//*49:*/
#line 1836 "./pp3.w"

struct nebula:public view_data{
int ngc,ic,messier;
string constellation;
double rectascension,declination;
double magnitude;
double diameter_x,diameter_y;
double horizontal_angle;
nebula_kind kind;
nebula():ngc(0),ic(0),messier(0),constellation(),rectascension(0.0),
declination(0.0),magnitude(0.0),diameter_x(0.0),
diameter_y(0.0),horizontal_angle(0.0),kind(unknown){}
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

typedef vector<nebula> nebulae_list;

/*:49*//*50:*/
#line 1861 "./pp3.w"

double nebula::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)const{
double penalties= view_data::penalties_with(left,right,top,bottom,core);
const double left2= x-radius,right2= x+radius,top2= y+radius,
bottom2= y-radius;
const double overlap_left= my_fmax(left,left2);
const double overlap_right= my_fmin(right,right2);
const double overlap_top= my_fmin(top,top2);
const double overlap_bottom= my_fmax(bottom,bottom2);
const double overlap_x= my_fdim(overlap_right,overlap_left);
const double overlap_y= my_fdim(overlap_top,overlap_bottom);
penalties+= overlap_x*overlap_y*params.penalties_nebula;
return penalties;
}

/*:50*//*51:*/
#line 1889 "./pp3.w"

istream&operator>>(istream&in,nebula&n){
int kind;
in>>n.ngc>>n.ic>>n.messier>>n.constellation>>n.rectascension
>>n.declination>>n.magnitude>>n.diameter_x>>n.diameter_y
>>n.horizontal_angle>>kind;
n.kind= nebula_kind(kind);
return in;
}

/*:51*//*52:*/
#line 1902 "./pp3.w"

void read_nebulae(nebulae_list&nebulae){
ifstream nebulae_file(params.filename_nebulae.c_str());
nebula current_nebula;
nebulae_file>>current_nebula;
while(nebulae_file){
/*53:*/
#line 1921 "./pp3.w"

string catalogue;
stringstream number;
if(current_nebula.messier> 0){
catalogue= "\\Messier{";
number<<current_nebula.messier;
}else if(current_nebula.ngc> 0){
catalogue= "\\NGC{";
number<<current_nebula.ngc;
}else if(current_nebula.ic> 0){
catalogue= "\\IC{";
number<<current_nebula.ic;
}else throw string("Invalid catalogue: \"")+catalogue+'"';
current_nebula.label= catalogue+number.str()+'}';


/*:53*/
#line 1908 "./pp3.w"

nebulae.push_back(current_nebula);
nebulae_file>>current_nebula;
}
}

/*:52*//*54:*/
#line 1946 "./pp3.w"

struct point{
double x,y;
point(const double x,const double y):x(x),y(y){}
point():x(0.0),y(0.0){}
};

/*:54*//*55:*/
#line 1968 "./pp3.w"

struct boundary{
vector<point> points;
vector<string> constellations;
bool belongs_to_constellation(const string constellation)const;
};

typedef vector<boundary> boundaries_list;

/*:55*//*56:*/
#line 1983 "./pp3.w"

bool boundary::belongs_to_constellation(const string constellation)const{
for(int i= 0;i<constellations.size();i++)
if(constellations[i].substr(0,3)==constellation.substr(0,3))
return true;
return false;
}

/*:56*//*57:*/
#line 2011 "./pp3.w"

istream&operator>>(istream&in,boundary&p){
int size;
in>>size;
if(!in.good())return in;
p.points.resize(size);
for(int i= 0;i<size;i++)
in>>p.points[i].x>>p.points[i].y;
in>>size;
p.constellations.resize(size);
for(int i= 0;i<size;i++)
in>>p.constellations[i];
return in;
}

/*:57*//*58:*/
#line 2029 "./pp3.w"

void read_constellation_boundaries(boundaries_list&boundaries){
ifstream boundaryfile(params.filename_boundaries.c_str());
boundary current_boundary;
boundaryfile>>current_boundary;
while(boundaryfile){
boundaries.push_back(current_boundary);
boundaryfile>>current_boundary;
}
}

/*:58*//*59:*/
#line 2051 "./pp3.w"

struct boundary_atom:public view_data{
point start,end;
boundary_atom(point start,point end);
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

/*:59*//*60:*/
#line 2067 "./pp3.w"

boundary_atom::boundary_atom(point start,point end):start(start),end(end){
x= (start.x+end.x)/2.0;
y= (start.y+end.y)/2.0;
radius= hypot(end.x-start.x,end.y-start.y)/2.0;
radius*= M_PI_2;
in_view= visible;
with_label= hidden;
skip= 0.0;
}

/*:60*//*61:*/
#line 2088 "./pp3.w"

/*63:*/
#line 2200 "./pp3.w"

bool line_intersection(double numerator,double denominator,
double zero_point,double slope,
double min,double max,
double&intersection){
if(denominator==0)return false;
const double lambda= numerator/denominator;
intersection= zero_point+lambda*slope;
return lambda> 0.0&&lambda<1.0&&
intersection> min&&intersection<max;
}

/*:63*/
#line 2089 "./pp3.w"


double boundary_atom::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)
const{
double intersection;
point r(end.x-start.x,end.y-start.y);
vector<point> intersection_points;
if(line_intersection(left-start.x,r.x,start.y,r.y,
bottom,top,intersection))
intersection_points.push_back(point(left,intersection));
if(line_intersection(right-start.x,r.x,start.y,r.y,
bottom,top,intersection))
intersection_points.push_back(point(right,intersection));
if(line_intersection(top-start.y,r.y,start.x,r.x,
left,right,intersection))
intersection_points.push_back(point(intersection,top));
if(line_intersection(bottom-start.y,r.y,start.x,r.x,
left,right,intersection))
intersection_points.push_back(point(intersection,bottom));
if(start.x> left&&start.x<right&&start.y> bottom&&start.y<top)
intersection_points.push_back(start);
if(end.x> left&&end.x<right&&end.y> bottom&&end.y<top)
intersection_points.push_back(end);
if(intersection_points.empty())return 0.0;
if(intersection_points.size()!=2){
cerr<<"pp3: Funny "<<intersection_points.size()
<<"-fold constellation boundary intersecrtion."<<endl;
return 0.0;
}
const double length= hypot(intersection_points[1].x-
intersection_points[0].x,
intersection_points[1].y-
intersection_points[0].y);
return(core?8.0*params.penalties_boundary:
0.5*params.penalties_boundary_rim)/72.27*2.54*length;
}

/*:61*//*62:*/
#line 2146 "./pp3.w"

struct connection:public view_data{
point start,end;
int from,to;
connection(const int from,const int to)
:from(from),to(to),start(),end(){in_view= visible;
with_label= hidden;skip= 0.0;}
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

typedef vector<connection> connections_list;

/*:62*//*64:*/
#line 2219 "./pp3.w"

double connection::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)const
{
double intersection;
point r(end.x-start.x,end.y-start.y);
vector<point> intersection_points;
if(line_intersection(left-start.x,r.x,start.y,r.y,
bottom,top,intersection))
intersection_points.push_back(point(left,intersection));
if(line_intersection(right-start.x,r.x,start.y,r.y,
bottom,top,intersection))
intersection_points.push_back(point(right,intersection));
if(line_intersection(top-start.y,r.y,start.x,r.x,
left,right,intersection))
intersection_points.push_back(point(intersection,top));
if(line_intersection(bottom-start.y,r.y,start.x,r.x,
left,right,intersection))
intersection_points.push_back(point(intersection,bottom));
if(start.x> left&&start.x<right&&start.y> bottom&&start.y<top)
intersection_points.push_back(start);
if(end.x> left&&end.x<right&&end.y> bottom&&end.y<top)
intersection_points.push_back(end);
if(intersection_points.empty())return 0.0;
if(intersection_points.size()!=2){
cerr<<"pp3: Funny "<<intersection_points.size()
<<"-fold constellation line intersecrtion."<<endl;
return 0.0;
}
const double length= hypot(intersection_points[1].x-
intersection_points[0].x,
intersection_points[1].y-
intersection_points[0].y);
return(core?8.0*params.penalties_cline:
0.5*params.penalties_cline_rim)/72.27*2.54*length;
}

/*:64*//*65:*/
#line 2268 "./pp3.w"

void read_constellation_lines(connections_list&connections,
const stars_list&stars){
ifstream file(params.filename_lines.c_str());
string from_catalogue_name,to_catalogue_name;
int from_catalogue_index= 0,to_catalogue_index= 0;
file>>to_catalogue_name;
while(file){
if(to_catalogue_name[0]=='#'){
string dummy;
getline(file,dummy);
}else if(to_catalogue_name==";")
from_catalogue_index= 0;
else{
file>>to_catalogue_index;
if(from_catalogue_index> 0&&to_catalogue_index> 0){
/*66:*/
#line 2296 "./pp3.w"

int from_index= -1,to_index= -1;
for(int i= 0;i<stars.size();i++){
/*67:*/
#line 2321 "./pp3.w"


if(from_index==-1)
if(from_catalogue_name=="HD"){
if(stars[i].hd==from_catalogue_index)from_index= i;
}else{
if(from_catalogue_name==stars[i].constellation)
if(stars[i].flamsteed==from_catalogue_index)
from_index= i;
}else if(to_index!=-1)break;

/*:67*/
#line 2299 "./pp3.w"

/*68:*/
#line 2336 "./pp3.w"


if(to_index==-1)
if(to_catalogue_name=="HD"){
if(stars[i].hd==to_catalogue_index)to_index= i;
}else{
if(to_catalogue_name==stars[i].constellation)
if(stars[i].flamsteed==to_catalogue_index)
to_index= i;
}else if(from_index!=-1)break;


/*:68*/
#line 2300 "./pp3.w"

}
if(from_index==-1||to_index==-1){
stringstream error_message;
error_message<<"Unrecognised star in constellation lines: ";
if(from_index==0)
error_message<<from_catalogue_name<<' '
<<from_catalogue_index;
else
error_message<<to_catalogue_name<<' '
<<to_catalogue_index;
throw error_message.str();
}
connections.push_back(connection(from_index,to_index));

/*:66*/
#line 2284 "./pp3.w"

}
from_catalogue_name= to_catalogue_name;
from_catalogue_index= to_catalogue_index;
}
file>>to_catalogue_name;
}
}

/*:65*//*71:*/
#line 2418 "./pp3.w"

void color::set(ostream&out)const{
out<<"\\newrgbcolor{dummycolor}{"<<red<<' '<<green<<' '<<blue
<<"}\\dummycolor\n  \\psset{linecolor=dummycolor}%\n";
}

/*:71*//*72:*/
#line 2430 "./pp3.w"

istream&operator>>(istream&in,color&c){
in>>c.red>>c.green>>c.blue;
if(!in
||c.red<0.0||c.red> 1.0
||c.green<0.0||c.green> 1.0
||c.blue<0.0||c.blue> 1.0)
throw string("Invalid RGB values in input script");
return in;
}

/*:72*//*73:*/
#line 2445 "./pp3.w"

ostream&operator<<(ostream&out,const color&c){
if(c.name.empty())throw string("Cannot write unnamed color to stream");
out<<"\\newrgbcolor{"<<c.name<<"}{"<<c.red<<' '<<c.green
<<' '<<c.blue<<"}%\n";
return out;
}

/*:73*//*74:*/
#line 2460 "./pp3.w"

color interpolate_colors(const double x,const color c1,const color c2,
const string new_name= ""){
if(x<0.0||x> 1.0)throw string("Invalid x for color interpolation");
const double y= 1.0-x;
return color(new_name,
y*c1.red+x*c2.red,
y*c1.green+x*c2.green,
y*c1.blue+x*c2.blue);
}





/*:74*//*76:*/
#line 2502 "./pp3.w"

class transformation{
double width,height,rad_per_cm,grad_per_cm0,ra0,delta0;

inline double stretch_factor(double z)const;
public:
transformation(const double rectascension,
const double declination,
const double width,const double height,
const double grad_per_cm);
bool polar_projection(const double rectascension,const double declination,
double&x,double&y)const;
double get_rad_per_cm()const{return rad_per_cm;}
};

/*:76*//*77:*/
#line 2575 "./pp3.w"

inline double transformation::stretch_factor(const double z)const{
const double zt= 1.0-z;
return 1.0+zt*
(1.0/3.0+zt*
(2.0/15.0+zt*
(2.0/35.0+zt*
(8.0/315.0+zt*
(8.0/693.0)))));
}

/*:77*//*78:*/
#line 2600 "./pp3.w"

transformation::transformation(const double rectascension,
const double declination,
const double width,const double height,
const double grad_per_cm){
ra0= (rectascension)*15.0*M_PI/180.0;
delta0= declination*M_PI/180.0;
rad_per_cm= grad_per_cm*M_PI/180.0;
grad_per_cm0= grad_per_cm;
transformation::width= width;
transformation::height= height;
}

/*:78*//*79:*/
#line 2622 "./pp3.w"

bool transformation::polar_projection(const double rectascension,
const double declination,
double&x,double&y)const{
const double ra= rectascension*15.0*M_PI/180.0;
const double delta= declination*M_PI/180.0;


const double ro= acos(sin(delta)*sin(delta0)+cos(delta)*cos(delta0)*cos(ra-ra0));
if(ro> M_PI/2+0.01/57.3)return false;
double sintheta= sin(ra0-ra)*cos(delta)/sin(ro);
double costheta= -1*(sin(delta)-cos(ro)*sin(delta0))/(sin(ro)*cos(delta0));
x= (2*tan(ro/2)*sintheta*44.9+width*grad_per_cm0/2)/grad_per_cm0;
y= (-2*tan(ro/2)*costheta*44.9+height*grad_per_cm0/2)/grad_per_cm0;
return true;
}


/*:79*//*81:*/
#line 2663 "./pp3.w"

double calculate_overlap(double left1,double right1,double top1,
double bottom1,double left2,double right2,
double top2,double bottom2){
const double overlap_left= my_fmax(left1,left2);
const double overlap_right= my_fmin(right1,right2);
const double overlap_top= my_fmin(top1,top2);
const double overlap_bottom= my_fmax(bottom1,bottom2);
const double overlap_x= my_fdim(overlap_right,overlap_left);
const double overlap_y= my_fdim(overlap_top,overlap_bottom);
return overlap_x*overlap_y;
}

/*:81*//*82:*/
#line 2684 "./pp3.w"

struct dimension{
double width,height,depth;
dimension():width(0.0),height(0.0),depth(0.0){}
dimension(const dimension&d):width(d.width),height(d.height),
depth(d.depth){}
};

typedef map<string,dimension> dimensions_list;

/*:82*//*83:*/
#line 2702 "./pp3.w"

/*122:*/
#line 4037 "./pp3.w"

void create_preamble(ostream&out){
out<<"\\documentclass["<<params.font_size<<"pt]{article}\n\n"
<<"\\nofiles"
<<"\\usepackage[dvips]{color}\n"
<<"\\usepackage{pstricks,pst-text}\n"
<<"\\newcommand*{\\DP}{.}\n"
<<"\\newcommand*{\\TicMark}[1]{#1}\n"
<<"\\newcommand*{\\Label}[1]{#1}\n"
<<"\\newcommand*{\\TextLabel}[1]{#1}\n"
<<"\\newcommand*{\\FlexLabel}[1]{#1}\n"
<<"\\newcommand*{\\Starname}[1]{#1}\n"
<<"\\newcommand*{\\Messier}[1]{M\\,#1}\n"
<<"\\newcommand*{\\NGC}[1]{NGC\\,#1}\n"
<<"\\newcommand*{\\IC}[1]{IC\\,#1}\n\n";

if(params.filename_preamble.empty())
out<<"\\usepackage{mathptmx}\n"
<<"\\usepackage{helvet}\n"
<<"\\AtBeginDocument{\\sffamily}\n";
else out<<"\\input "<<params.filename_preamble<<'\n';
}

/*:122*/
#line 2703 "./pp3.w"

/*89:*/
#line 2916 "./pp3.w"

void recalculate_dimensions(dimensions_list&dimensions,
const objects_list&objects)
{
list<string> required_names;
for(int i= 0;i<objects.size();i++){
const string current_name= objects[i]->label;
if(!current_name.empty())required_names.push_back(current_name);
}
required_names.unique();

ofstream temp_file("pp3temp.tex");
create_preamble(temp_file);
temp_file<<"\n\\begin{document}\n"
<<"\\newwrite\\labelsfile\n"
<<"\\catcode`\\_=11  % for underscores in the filename\n"
<<"\\immediate\\openout\\labelsfile=pp3temp.dat\n"
<<"\\catcode`\\_=8\n";
list<string> ::const_iterator p= required_names.begin();
while(p!=required_names.end())
temp_file<<"\\setbox0 = \\hbox{\\Label{"<<*(p++)
<<"}}\n  \\immediate\\write\\labelsfile{"
"\\the\\wd0s \\the\\ht0s \\the\\dp0s}\n";
temp_file<<"\\immediate\\closeout\\labelsfile\n\\end{document}\n";
temp_file.close();
string commandline("latex pp3temp");
if(params.filename_output.empty())
commandline+= " > pp3dump.log";
if(system(commandline.c_str())!=0)
throw string("Label dimensions calculations: LaTeX call failed: ")
+commandline;

ifstream raw_labels_file("pp3temp.dat");
p= required_names.begin();
while(p!=required_names.end()){
string current_width,current_height,current_depth;
string current_name;
current_name= *(p++);
raw_labels_file>>current_width>>current_height>>current_depth;
current_width.substr(0,current_width.length()-3);
current_height.substr(0,current_height.length()-3);
current_depth.substr(0,current_depth.length()-3);
dimensions[current_name].width= strtod(current_width.c_str(),0)
/72.27*2.54;
dimensions[current_name].height= strtod(current_height.c_str(),0)
/72.27*2.54;
dimensions[current_name].depth= strtod(current_depth.c_str(),0)
/72.27*2.54;
dimensions[current_name].height+= dimensions[current_name].depth;
}

/*90:*/
#line 2974 "./pp3.w"

ofstream cooked_labels_file("labeldimens.dat");
cooked_labels_file.setf(ios::fixed);
cooked_labels_file.precision(5);
dimensions_list::const_iterator q= dimensions.begin();
while(q!=dimensions.end()){
string current_name;
dimension current_dimension;
current_name= q->first;
current_dimension= (q++)->second;
cooked_labels_file<<current_name<<'\n'
<<current_dimension.width<<' '
<<current_dimension.height<<' '
<<current_dimension.depth
<<'\n';
}


/*:90*/
#line 2967 "./pp3.w"

}

/*:89*/
#line 2704 "./pp3.w"


void arrange_labels(objects_list&objects,dimensions_list&dimensions){
objects_list vicinity;
/*88:*/
#line 2868 "./pp3.w"

bool dimensions_recalculated= false;
for(int i= 0;i<objects.size();i++){
view_data*current_object= objects[i];
if(current_object->with_label==visible){
if(!dimensions_recalculated&&
dimensions.find(current_object->label)==dimensions.end()){
recalculate_dimensions(dimensions,objects);
dimensions_recalculated= true;
if(dimensions.find(current_object->label)==dimensions.end())
throw string("Update of label dimensions file failed: \"")+
current_object->label+"\" not found";
}
current_object->label_width= dimensions[current_object->label].width;
current_object->label_height= 
dimensions[current_object->label].height;
current_object->label_depth= dimensions[current_object->label].depth;
}
}


/*:88*/
#line 2708 "./pp3.w"

for(int i= 0;i<objects.size();i++){
vicinity.clear();
if(objects[i]->in_view==visible&&objects[i]->with_label==visible
&&!objects[i]->label_arranged){
/*84:*/
#line 2784 "./pp3.w"

const double on_object_scope= objects[i]->scope();
for(int j= 0;j<objects.size();j++){
if(i!=j&&objects[j]->in_view==visible){
const double distance= 
hypot(objects[i]->x-objects[j]->x,
objects[i]->y-objects[j]->y);
if(distance<on_object_scope+objects[j]->scope()&&
/*85:*/
#line 2797 "./pp3.w"

(distance> objects[j]->skip||
(objects[j]->with_label==visible&&!objects[j]->label.empty()))

/*:85*/
#line 2792 "./pp3.w"
)
vicinity.push_back(objects[j]);
}
}

/*:84*/
#line 2713 "./pp3.w"

double best_penalty= DBL_MAX;
int best_angle= 0;
for(int k= 0;k<8;k++){
objects[i]->label_angle= k;
double on_object_left,on_object_right,on_object_top,
on_object_bottom;
objects[i]->
get_label_boundaries(on_object_left,on_object_right,
on_object_top,on_object_bottom);
double penalty= 0.0;
double rim_width= 2.0*objects[i]->skip;
for(int j= 0;j<vicinity.size();j++){
penalty+= vicinity[j]->
penalties_with(on_object_left,on_object_right,
on_object_top,on_object_bottom)+
vicinity[j]->
penalties_with(on_object_left-rim_width,
on_object_right+rim_width,
on_object_top+rim_width,
on_object_bottom-rim_width,
false)*params.penalties_rim;
}
if(on_object_left<0.0||on_object_bottom<0.0||
on_object_right> params.view_frame_width||
on_object_top> params.view_frame_height)
penalty+= 10000.0;
if(penalty<best_penalty){
best_penalty= penalty;
best_angle= k;
}
}
if(!objects[i]->label.empty())
if(best_penalty<0.4*params.penalties_threshold*
objects[i]->label_height*objects[i]->label_width){
objects[i]->label_angle= best_angle;
objects[i]->label_arranged= true;
#ifdef DEBUG
stringstream penalty;
penalty.precision(2);
penalty<<" "<<best_penalty<<" ("
<<best_penalty/
(objects[i]->label_height*objects[i]->label_width)
*100<<"%)";

cerr<<"pp3DEBUG: Object "<<objects[i]->label<<' ';
const star*s= dynamic_cast<star*> (objects[i]);
if(s)cerr<<s->constellation;
cerr<<" has penalty of"<<penalty.str()<<endl;
#endif
}else{
objects[i]->with_label= hidden;
objects[i]->label_arranged= true;
}
}
}
}

/*:83*//*86:*/
#line 2807 "./pp3.w"

void print_labels(const objects_list&objects){
for(int i= 0;i<objects.size();i++)
if(objects[i]->in_view==visible&&objects[i]->with_label==visible
&&objects[i]->label_arranged){
double left,right,top,bottom;
objects[i]->get_label_boundaries(left,right,top,bottom);
if(left<0.0||bottom<0.0||right> params.view_frame_width
||top> params.view_frame_height)continue;

objects[i]->label_color.set(OUT);
OUT<<"\\hbox to 0pt{";
OUT<<"\\hskip"<<left<<"cm";
OUT<<"\\vbox to 0pt{\\vss\n  \\hbox{\\Label{";
OUT<<objects[i]->label;
OUT<<"}}\\vskip"<<bottom<<"cm";
OUT<<"\\hrule height 0pt}\\hss}%\n";
#ifdef DEBUG
OUT<<"\\psframe[linewidth=0.1pt]("<<left<<','<<bottom
<<")("<<right<<','<<bottom+objects[i]->label_depth<<")%\n";
OUT<<"\\psframe[linewidth=0.3pt]("<<left<<','<<bottom
<<")("<<right<<','<<top<<")%\n";
#endif
}
}

/*:86*//*87:*/
#line 2842 "./pp3.w"

void read_label_dimensions(dimensions_list&dimensions){
ifstream file(params.filename_dimensions.c_str());
string name,dummy;
getline(file,name);
while(file){
file>>dimensions[name].width>>dimensions[name].height
>>dimensions[name].depth;
getline(file,dummy);
getline(file,name);
}
}

/*:87*//*91:*/
#line 2999 "./pp3.w"

struct text:public view_data{
string contents;
double rectascension,declination;
text(string t,double r,double d,color c,int angle,bool on_baseline);
};

typedef list<text> texts_list;

/*:91*//*92:*/
#line 3014 "./pp3.w"

text::text(string t,double r,double d,color c,int angle,bool on_baseline)
:contents(t),rectascension(r),declination(d){
label= string("\\TextLabel{")+t+'}';
with_label= visible;
label_angle= angle;
view_data::on_baseline= on_baseline;
label_arranged= true;
label_color= c;
radius= skip= 0.0;
}

/*:92*//*93:*/
#line 3031 "./pp3.w"

void draw_text_labels(transformation&mytransform,texts_list&texts,
objects_list&objects){
texts_list::iterator p= texts.begin();
while(p!=texts.end()){
double x,y;
if(mytransform.polar_projection(p->rectascension,
p->declination,
x,y)){
p->in_view= visible;
p->x= x;
p->y= y;
objects.push_back(&(*p));
}
p++;
}
}

/*:93*//*94:*/
#line 3069 "./pp3.w"

struct flex_label:public view_data{
double rectascension,declination;
flex_label(string s,double r,double d,color c,int a,bool b);
virtual bool draw(const transformation&mytransform,
dimensions_list&dimensions,objects_list&objects)
const= 0;
};

/*:94*//*95:*/
#line 3085 "./pp3.w"

flex_label::flex_label(string s,double r,double d,color c,int a,bool b)
:rectascension(r),declination(d){
label_color= c;
label= string("\\FlexLabel{")+s+'}';
label_angle= a;
on_baseline= b;
in_view= visible;
with_label= hidden;
label_arranged= true;
}

typedef list<flex_label*> flexes_list;

/*:95*//*96:*/
#line 3102 "./pp3.w"

struct declination_flex:public flex_label{
declination_flex(string s,double r,double d,color c,int a,bool b)
:flex_label(s,r,d,c,a,b){}
virtual bool draw(const transformation&mytransform,
dimensions_list&dimensions,objects_list&objects)
const;
virtual double penalties_with(const double left,const double right,
const double top,const double bottom,
bool core= true)const;
};

/*:96*//*97:*/
#line 3133 "./pp3.w"

bool declination_flex::draw(const transformation&mytransform,
dimensions_list&dimensions,
objects_list&objects)const{
if(dimensions.find(label)==dimensions.end())
recalculate_dimensions(dimensions,objects);
if(dimensions.find(label)==dimensions.end())
throw string("Update of label dimensions file failed: \"")+
label+"\" not found";
const double label_width= dimensions[label].width;
const double label_height= dimensions[label].height;
const double rectascension_halfwidth= label_width
*mytransform.get_rad_per_cm()*180.0/M_PI/15.0
/cos(declination*M_PI/180.0)/2.0;
char justification;
double path_point_rectascension[3];
path_point_rectascension[0]= rectascension;
path_point_rectascension[1]= rectascension-rectascension_halfwidth;
path_point_rectascension[2]= rectascension-
2.0*rectascension_halfwidth;
switch(label_angle){
case 0:case 1:case 7:
justification= 'l';
break;
case 2:case 6:
justification= 'c';
for(int i= 0;i<3;i++)
path_point_rectascension[i]+= rectascension_halfwidth;
break;
case 3:case 4:case 5:
justification= 'r';
for(int i= 0;i<3;i++)
path_point_rectascension[i]+= 2.0*rectascension_halfwidth;
break;
}
double lower;
switch(label_angle){
case 0:case 4:lower= -0.4;break;
case 1:case 2:case 3:lower= 0.0;break;
case 5:case 6:case 7:lower= -0.8;break;
}
double x[3],y[3];
for(int i= 0;i<3;i++)
if(!mytransform.polar_projection(path_point_rectascension[i],
declination,x[i],y[i]))
return false;

label_color.set(OUT);
OUT<<"\\Label{\\pstextpath["<<justification
<<"](0,"<<lower<<"em){\\pscurve[linestyle=none]%\n  ";
for(int i= 0;i<3;i++)
OUT<<'('<<x[i]<<"cm,"<<y[i]<<"cm)";
OUT<<"}{\\dummycolor"<<label<<"}}%\n";

return true;
}

/*:97*//*98:*/
#line 3193 "./pp3.w"

double declination_flex::penalties_with(const double left,const double right,
const double top,const double bottom,
bool core)const{
return 0.0;
}

/*:98*//*99:*/
#line 3208 "./pp3.w"

void draw_flex_labels(const transformation&mytransform,
const flexes_list&flexes,objects_list&objects,
dimensions_list&dimensions){
flexes_list::const_iterator p= flexes.begin();
while(p!=flexes.end())objects.push_back(*p++);
p= flexes.begin();
while(p!=flexes.end())(*p++)->draw(mytransform,dimensions,objects);
}

/*:99*//*100:*/
#line 3233 "./pp3.w"

/*101:*/
#line 3284 "./pp3.w"

void create_hs_colour(double b_v,string spectral_class){
double hue,saturation;
const double bv0= -0.1,bv1= 0.001,bv2= 0.62,bv3= 1.7;
const double hue0= 0.6,hue1= 0.47,hue2= 0.17,hue3= 0.0;
const double min_saturation= 0.0,max_saturation= 0.2;
/*102:*/
#line 3319 "./pp3.w"

if(b_v> 90.0){
switch(spectral_class[0]){
case'O':b_v= 0.0;break;
case'B':b_v= -0.07;break;
case'A':b_v= 0.11;break;
case'F':b_v= 0.43;break;
case'G':b_v= 0.89;break;
case'K':b_v= 1.24;break;
case'M':b_v= 1.62;break;
case'N':b_v= 2.88;break;
case'S':b_v= 1.84;break;
case'C':b_v= 3.02;break;
default:b_v= 0.0;break;
}
}


/*:102*/
#line 3290 "./pp3.w"

if(b_v<bv0)b_v= bv0;
if(b_v> bv3)b_v= bv3;
if(b_v<bv1){
hue= (b_v-bv0)/(bv1-bv0)
*(hue1-hue0)+hue0;
saturation= (b_v-bv0)/(bv1-bv0)
*(min_saturation-max_saturation)+max_saturation;
}
else if(b_v<bv2){
hue= 0.3;
saturation= 0;
}
else{
hue= (b_v-bv2)/(bv3-bv2)
*(hue3-hue2)+hue2;
saturation= (b_v-bv2)/(bv3-bv2)
*(max_saturation-min_saturation)+min_saturation;
}
OUT<<hue<<' '<<saturation;
}

/*:101*/
#line 3234 "./pp3.w"


void draw_stars(const transformation&mytransform,stars_list&stars,
objects_list&objects){
for(int i= 0;i<stars.size();i++)
if(stars[i].in_view!=hidden&&
stars[i].magnitude<params.faintest_star_magnitude){

if(mytransform.polar_projection(stars[i].rectascension,
stars[i].declination,
stars[i].x,stars[i].y)){
stars[i].in_view= visible;
const double m_dot= params.faintest_star_disk_magnitude;
const double r_min= params.minimal_star_radius/
params.star_scaling;
stars[i].radius= params.star_scaling*
(stars[i].magnitude<m_dot?
sqrt((m_dot-stars[i].magnitude)/300.0+r_min*r_min)
:r_min);
if(stars[i].with_label==undecided)
stars[i].with_label= 
(stars[i].magnitude<
params.faintest_star_with_label_magnitude&&
!stars[i].name.empty())?visible:hidden;
if(params.colored_stars){
OUT<<"\\newhsbcolor{starcolor}{";
create_hs_colour(stars[i].b_v,stars[i].spectral_class);
OUT<<" 1}%\n";
}else OUT<<params.starcolor;
OUT<<"\\pscircle*[linecolor=starcolor]("
<<stars[i].x<<","
<<stars[i].y<<"){"
<<stars[i].radius/2.54*72.27<<"pt}%\n";
objects.push_back(&stars[i]);
}else stars[i].in_view= hidden;
}else stars[i].in_view= stars[i].with_label= hidden;
}

/*:100*//*103:*/
#line 3361 "./pp3.w"

void draw_nebulae(const transformation&mytransform,nebulae_list&nebulae,
objects_list&objects){
OUT<<"\\psset{linecolor=nebulacolor,linewidth="
<<params.linewidth_nebula<<"cm,linestyle="
<<params.linestyle_nebula<<",curvature=1 .5 -1}%\n";
for(int i= 0;i<nebulae.size();i++)
if(nebulae[i].in_view==visible||
(nebulae[i].in_view==undecided&&
(((nebulae[i].kind==open_cluster||
nebulae[i].kind==globular_cluster)
&&nebulae[i].magnitude<params.faintest_cluster_magnitude)
||
((nebulae[i].kind==galaxy||nebulae[i].kind==reflection||
nebulae[i].kind==emission)&&
nebulae[i].magnitude<params.faintest_diffuse_nebula_magnitude)
||
nebulae[i].messier> 0))){
if(mytransform.polar_projection(nebulae[i].rectascension,
nebulae[i].declination,
nebulae[i].x,nebulae[i].y)){
nebulae[i].in_view= visible;
if(nebulae[i].horizontal_angle> 360.0)
nebulae[i].diameter_x= nebulae[i].diameter_y= 
sqrt(nebulae[i].diameter_x*nebulae[i].diameter_y);
nebulae[i].radius= nebulae[i].diameter_x/2.0/
mytransform.get_rad_per_cm()*M_PI/180.0;
if(nebulae[i].with_label!=hidden)
nebulae[i].with_label= visible;
if(nebulae[i].radius> params.minimal_nebula_radius){
/*104:*/
#line 3418 "./pp3.w"

if(nebulae[i].diameter_x==nebulae[i].diameter_y)
OUT<<"\\pscircle("<<nebulae[i].x<<','<<nebulae[i].y
<<"){"<<nebulae[i].radius<<"}%\n";
else{
double rectascension[4],declination[4];
const double r_scale= 1.0/cos(nebulae[i].declination*M_PI/180.0);
const double cos_angle
= cos(nebulae[i].horizontal_angle*M_PI/180.0);
const double sin_angle
= sin(nebulae[i].horizontal_angle*M_PI/180.0);
const double half_x= nebulae[i].diameter_x/2.0;
const double half_y= nebulae[i].diameter_y/2.0;
rectascension[0]= nebulae[i].rectascension-
half_x*cos_angle/15.0*r_scale;
declination[0]= nebulae[i].declination-
half_x*sin_angle;
rectascension[1]= nebulae[i].rectascension+
half_y*sin_angle/15.0*r_scale;
declination[1]= nebulae[i].declination-
half_y*cos_angle;
rectascension[2]= nebulae[i].rectascension+
half_x*cos_angle/15.0*r_scale;
declination[2]= nebulae[i].declination+
half_x*sin_angle;
rectascension[3]= nebulae[i].rectascension-
half_y*sin_angle/15.0*r_scale;
declination[3]= nebulae[i].declination+
half_y*cos_angle;
OUT<<"\\psccurve";
for(int j= 0;j<4;j++){
double x,y;
mytransform.polar_projection(rectascension[j],
declination[j],x,y);
OUT<<'('<<x<<','<<y<<')';
}
}
OUT<<"\\relax\n";


/*:104*/
#line 3391 "./pp3.w"

}else{
nebulae[i].radius= params.minimal_nebula_radius;
OUT<<"\\pscircle("
<<nebulae[i].x<<","
<<nebulae[i].y<<"){"
<<nebulae[i].radius/2.54*72.27<<"pt}%\n";
}
objects.push_back(&nebulae[i]);
}else nebulae[i].in_view= hidden;
}else nebulae[i].in_view= nebulae[i].with_label= hidden;
}

/*:103*//*106:*/
#line 3488 "./pp3.w"

inline void add_curve_point(const double rectascension,
const double declination,
const transformation&transform,
const int i,bool&within_curve,
const int steps){
static double last_x,last_y;
double x,y;
if(transform.polar_projection(rectascension,declination,x,y)){
if(!within_curve){
OUT<<"\\pscurve"<<"("<<x<<','<<y<<")";
within_curve= true;
}else if(i%steps==0)OUT<<"("<<x<<','<<y<<")";
if(i%(steps*4)==0||steps==1)OUT<<"%\n";

}else
if(within_curve){
OUT<<"("<<last_x<<','<<last_y<<")"<<"\\relax\n";
within_curve= false;
}
last_x= x;last_y= y;
}

/*:106*//*107:*/
#line 3533 "./pp3.w"

void create_grid(const transformation transform,
const double scans_per_cm= 10,
const double point_distance= 5.0){
if(!params.show_grid&&!params.show_ecliptic&&!params.show_horizon)return;
const double scans_per_fullcircle= 
scans_per_cm/transform.get_rad_per_cm()*2.0*M_PI;
const int steps= int((point_distance*M_PI/180.0)*
(scans_per_fullcircle/(2.0*M_PI)))+2;
bool within_curve;
if(params.show_grid){
OUT<<"\\psset{linestyle="<<params.linestyle_grid
<<",linecolor=gridcolor,linewidth="
<<params.linewidth_grid<<"cm}%\n";
/*108:*/
#line 3581 "./pp3.w"

for(int declination= -80;declination<=80;declination+= 10){
if(declination==0)
OUT<<"\\psset{linewidth="<<2.0*params.linewidth_grid
<<"cm}%\n";
within_curve= false;
const int number_of_points= 
int(cos(declination*M_PI/180.0)*scans_per_fullcircle);
for(int i= 0;i<=number_of_points;i++)
add_curve_point(double(i)/double(number_of_points)*24.0,
declination,transform,i,within_curve,
i==number_of_points?1:steps);
if(declination==0)
OUT<<"\\psset{linewidth="<<params.linewidth_grid<<"cm}%\n";
}

/*:108*/
#line 3547 "./pp3.w"

/*109:*/
#line 3601 "./pp3.w"

const int number_of_points= int(scans_per_fullcircle/2.0);
for(int rectascension= 0;rectascension<=23;rectascension++){
within_curve= false;
for(int i= 0;i<=number_of_points;i++)
add_curve_point(double(rectascension),
double(i)/double(number_of_points)*160.0-80.0,
transform,i,within_curve,
i==number_of_points?1:steps);
}

/*:109*/
#line 3548 "./pp3.w"

}
if(params.show_ecliptic){
/*110:*/
#line 3631 "./pp3.w"

OUT<<"\\psset{linestyle="<<params.linestyle_ecliptic
<<",linecolor=eclipticcolor,"
<<"linewidth="<<params.linewidth_ecliptic<<"cm}%\n";

{
const double epsilon= 23.44*M_PI/180.0;
const int number_of_points= int(scans_per_fullcircle);
within_curve= false;
for(int i= 0;i<=number_of_points;i++){
const double phi= double(i)/double(number_of_points)*2*M_PI;
const double delta= atan(tan(epsilon)*sin(-phi));
add_curve_point((2*M_PI-phi)*12.0/M_PI,delta*180.0/M_PI,
transform,i,within_curve,
i==number_of_points?1:steps);
}
}


/*:110*/
#line 3551 "./pp3.w"

}
if(params.show_horizon){
OUT<<"\\psset{linestyle="<<params.linestyle_horizon
<<",linecolor=horizoncolor,"
<<"linewidth="<<params.linewidth_horizon<<"cm}%\n";

{
const double decl= (90-params.center_declination)*M_PI/180.0;
const int number_of_points= 1.5*int(scans_per_fullcircle);
within_curve= false;
for(int i= 0;i<=number_of_points;i++){
const double phi= double(i)/double(number_of_points)*2*M_PI;
const double delta= atan(tan(decl)*sin(phi-M_PI/2+params.center_rectascension*15*M_PI/180));
add_curve_point((2*M_PI-phi)*12.0/M_PI,delta*180.0/M_PI,
transform,i,within_curve,
i==number_of_points?1:steps);
}
}
}
}

/*:107*//*112:*/
#line 3670 "./pp3.w"

void draw_boundary_line(const boundary&b,const transformation&transform,
objects_list&objects,bool highlighted= false){
vector<point> current_line;
for(int j= 0;j<b.points.size();j++){
const double rectascension= b.points[j].x;
const double declination= b.points[j].y;
double x,y;
if(!transform.polar_projection(rectascension,declination,x,y))
continue;
current_line.push_back(point(x,y));
}
if(current_line.size()>=2){
if(current_line.size()==2)OUT<<"\\psline";
else OUT<<"\\pscurve";
OUT<<"[liftpen=2]{c-c}";
for(int j= 0;j<current_line.size();j++){
OUT<<'('<<current_line[j].x<<','
<<current_line[j].y<<')';
if(j%4==3)OUT<<"%\n";
if(highlighted)
/*113:*/
#line 3702 "./pp3.w"

if(j> 0)objects.push_back(new boundary_atom(current_line[j],
current_line[j-1]));

/*:113*/
#line 3691 "./pp3.w"

}
OUT<<"\\relax\n";
}
}

/*:112*//*114:*/
#line 3718 "./pp3.w"

void draw_boundaries(const transformation&mytransform,
boundaries_list&boundaries,
objects_list&objects,
string constellation= string("")){
OUT<<"\\psset{linecolor=boundarycolor,linewidth="
<<params.linewidth_boundary<<"cm,"
<<"linestyle="<<params.linestyle_boundary<<"}%\n";
if(!constellation.empty()){
for(int i= 0;i<boundaries.size();i++)
if(!boundaries[i].belongs_to_constellation(constellation))
draw_boundary_line(boundaries[i],mytransform,objects);
OUT<<"\\psset{linecolor=hlboundarycolor,linewidth="
<<params.linewidth_boundary<<"cm,"<<"linestyle="
<<params.linestyle_hlboundary<<"}%\n";
OUT<<"\\pscustom{";
for(int i= 0;i<boundaries.size();i++)
if(boundaries[i].belongs_to_constellation(constellation))
draw_boundary_line(boundaries[i],mytransform,objects,true);
OUT<<"}%\n";
}else
for(int i= 0;i<boundaries.size();i++)
draw_boundary_line(boundaries[i],mytransform,objects);
}

/*:114*//*115:*/
#line 3760 "./pp3.w"

void draw_constellation_lines(connections_list&connections,
const stars_list&stars,
objects_list&objects){
OUT<<"\\psset{linecolor=clinecolor,linestyle="<<params.linestyle_cline
<<",linewidth="<<params.linewidth_cline<<"cm}%\n";
for(int i= 0;i<connections.size();i++)
if((stars[connections[i].from].in_view==visible||
stars[connections[i].to].in_view==visible)
&&stars[connections[i].from].has_valid_coordinates()
&&stars[connections[i].to].has_valid_coordinates()){
double x1= stars[connections[i].from].x;
double y1= stars[connections[i].from].y;
double x2= stars[connections[i].to].x;
double y2= stars[connections[i].to].y;
const double phi= atan2(y2-y1,x2-x1);
double r= hypot(x2-x1,y2-y1);
double skip;
skip= stars[connections[i].from].radius+
stars[connections[i].from].skip;
r-= skip;
x1+= skip*cos(phi);
y1+= skip*sin(phi);
skip= stars[connections[i].to].radius+
stars[connections[i].to].skip;
r-= skip;
x2-= skip*cos(phi);
y2-= skip*sin(phi);
connections[i].radius= r/2.0;
connections[i].x= (x1+x2)/2.0;
connections[i].y= (y1+y2)/2.0;
if(r> params.shortest_constellation_line&&r> 0.0){
OUT<<"\\psline{cc-cc}("<<x1<<','<<y1
<<")("<<x2<<','<<y2<<")%\n";
connections[i].start= point(x1,y1);
connections[i].end= point(x2,y2);
objects.push_back(&connections[i]);
}
}

}


/*:115*//*116:*/
#line 3821 "./pp3.w"

void draw_milky_way(const transformation&mytransform){
vector<vector<point> > pixels(256);
/*69:*/
#line 2374 "./pp3.w"

ifstream file(params.filename_milkyway.c_str());
double radius;
file>>radius;
double rectascension,declination,x,y;
int pixel;
const double cm_per_grad= 1.0/
(mytransform.get_rad_per_cm()*180.0/M_PI);
radius*= cm_per_grad/2.54*72.27;
file>>rectascension>>declination>>pixel;
while(file){
if(mytransform.polar_projection(rectascension,declination,x,y))
pixels[pixel].push_back(point(x,y));
file>>rectascension>>declination>>pixel;
}


/*:69*/
#line 3824 "./pp3.w"

for(int i= 1;i<pixels.size();i++){
if(pixels[i].size()==0)continue;
interpolate_colors(double(i)/255.0,params.bgcolor,
params.milkywaycolor).set(OUT);
for(int j= 0;j<pixels[i].size();j++)
OUT<<"\\qdisk("<<pixels[i][j].x<<","<<pixels[i][j].y
<<"){"<<radius<<"pt}%\n";
}
}


/*:116*//*117:*/
#line 3851 "./pp3.w"

/*11:*/
#line 498 "./pp3.w"

bool read_boolean(istream&script){
string boolean;
script>>boolean;
if(boolean=="on")return true;
else if(boolean=="off")return false;
else throw string("Expected \"on\" or \"off\" in \"switch\" construct "
"in input script");
}

/*:11*//*12:*/
#line 520 "./pp3.w"

string read_string(istream&script){
const string UnexpectedEOS("Unexpected end of input script while reading a"
" string parameter");
char c;
string contents;
while(script.get(c))if(!isspace(c))break;
if(!script)throw UnexpectedEOS;
if(c!='"'){
script>>contents;
if(script)contents.insert(contents.begin(),c);else contents= c;
}else{
while(script.get(c)){
if(c=='"')break;
if(c=='\\'){
if(!script.get(c))
throw UnexpectedEOS;
switch(c){
case'\\':case'"':contents+= c;break;
default:throw string("Unknown escape sequence in string");
}
}else contents+= c;
}
if(!script)
throw UnexpectedEOS;
}
return contents;
}

/*:12*//*13:*/
#line 561 "./pp3.w"

void read_parameters_from_script(istream&script){
string opcode;
script>>opcode;
while(opcode!="objects_and_labels"&&script){
if(opcode[0]=='#'){
string rest_of_line;
getline(script,rest_of_line);
}else
/*14:*/
#line 612 "./pp3.w"

if(opcode=="color"){
string color_name;
script>>color_name;
if(color_name=="background")script>>params.bgcolor;
else if(color_name=="grid")script>>params.gridcolor;
else if(color_name=="ecliptic")script>>params.eclipticcolor;
else if(color_name=="horizon")script>>params.horizoncolor;
else if(color_name=="boundaries")
script>>params.boundarycolor;
else if(color_name=="highlighted_boundaries")
script>>params.hlboundarycolor;
else if(color_name=="stars")script>>params.starcolor;
else if(color_name=="nebulae")script>>params.nebulacolor;
else if(color_name=="labels")script>>params.labelcolor;
else if(color_name=="text_labels")
script>>params.textlabelcolor;
else if(color_name=="constellation_lines")
script>>params.clinecolor;
else if(color_name=="milky_way")script>>params.milkywaycolor;
else throw string("Undefined \"color\" construct"
" in input script: \"")+color_name+'"';
}

/*:14*/
#line 570 "./pp3.w"

else
/*15:*/
#line 650 "./pp3.w"

if(opcode=="line_width"){
string line_name;
script>>line_name;
if(line_name=="grid")script>>params.linewidth_grid;
else if(line_name=="ecliptic")
script>>params.linewidth_ecliptic;
else if(line_name=="horizon")
script>>params.linewidth_horizon;
else if(line_name=="boundaries")
script>>params.linewidth_boundary;
else if(line_name=="highlighted_boundaries")
script>>params.linewidth_hlboundary;
else if(line_name=="nebulae")
script>>params.linewidth_nebula;
else if(line_name=="constellation_lines")
script>>params.linewidth_cline;
else throw string("Undefined \"line_width\" construct"
" in input script: \"")+line_name+'"';
}

/*:15*/
#line 572 "./pp3.w"

else
/*16:*/
#line 689 "./pp3.w"

if(opcode=="line_style"){
string line_name;
script>>line_name;
if(line_name=="grid")script>>params.linestyle_grid;
else if(line_name=="ecliptic")
script>>params.linestyle_ecliptic;
else if(line_name=="horizon")
script>>params.linestyle_horizon;
else if(line_name=="boundaries")
script>>params.linestyle_boundary;
else if(line_name=="highlighted_boundaries")
script>>params.linestyle_hlboundary;
else if(line_name=="nebulae")
script>>params.linestyle_nebula;
else if(line_name=="constellation_lines")
script>>params.linestyle_cline;
else throw string("Undefined \"line_width\" construct"
" in input script: \"")+line_name+'"';
}


/*:16*/
#line 574 "./pp3.w"

else
/*17:*/
#line 732 "./pp3.w"

if(opcode=="switch"){
string switch_name;
script>>switch_name;
if(switch_name=="milky_way")
params.milkyway_visible= read_boolean(script);
else if(switch_name=="nebulae")
params.nebulae_visible= read_boolean(script);
else if(switch_name=="colored_stars")
params.colored_stars= read_boolean(script);
else if(switch_name=="grid")
params.show_grid= read_boolean(script);
else if(switch_name=="ecliptic")
params.show_ecliptic= read_boolean(script);
else if(switch_name=="horizon")
params.show_horizon= read_boolean(script);
else if(switch_name=="boundaries")
params.show_boundaries= read_boolean(script);
else if(switch_name=="constellation_lines")
params.show_lines= read_boolean(script);
else if(switch_name=="labels")
params.show_labels= read_boolean(script);
else if(switch_name=="eps_output")
params.create_eps= read_boolean(script);
else if(switch_name=="pdf_output")
params.create_pdf= read_boolean(script);
else throw string("Undefined \"switch\" construct"
" in input script: \"")+switch_name+'"';
}

/*:17*/
#line 576 "./pp3.w"

else
/*18:*/
#line 802 "./pp3.w"

if(opcode=="penalties"){
string penalty_name;
double value;
script>>penalty_name>>value;
value/= 1000.0;
if(penalty_name=="stars")
params.penalties_star= value;
else if(penalty_name=="labels")
params.penalties_label= value;
else if(penalty_name=="nebulae")
params.penalties_nebula= value;
else if(penalty_name=="boundaries")
params.penalties_boundary= value;
else if(penalty_name=="boundaries_rim")
params.penalties_boundary_rim= value;
else if(penalty_name=="constellation_lines")
params.penalties_cline= value;
else if(penalty_name=="constellation_lines_rim")
params.penalties_cline_rim= value;
else if(penalty_name=="threshold")
params.penalties_threshold= value;
else if(penalty_name=="rim")
params.penalties_rim= value;
else throw string("Undefined \"penalties\" construct"
" in input script: \"")+penalty_name+'"';
}

/*:18*/
#line 578 "./pp3.w"

else
/*19:*/
#line 866 "./pp3.w"

if(opcode=="filename"){
string object_name;
script>>object_name;
if(object_name=="output")
params.filename_output= read_string(script);
else if(object_name=="stars")
params.filename_stars= read_string(script);
else if(object_name=="nebulae")
params.filename_nebulae= read_string(script);
else if(object_name=="label_dimensions")
params.filename_dimensions= read_string(script);
else if(object_name=="constellation_lines")
params.filename_lines= read_string(script);
else if(object_name=="boundaries")
params.filename_boundaries= read_string(script);
else if(object_name=="milky_way")
params.filename_milkyway= read_string(script);
else if(object_name=="latex_preamble")
params.filename_preamble= read_string(script);
else if(object_name=="include"){
if(!params.filename_include.empty())
throw string("Nesting depth of include files greater"
" than one");
params.filename_include= read_string(script);
ifstream included_script(params.filename_include.c_str());
if(!included_script.good())
cerr<<"pp3: Warning: included file "
<<params.filename_include
<<" not found; ignored"<<endl;
else read_parameters_from_script(included_script);
}
else throw string("Undefined \"filename\" construct"
" in input script: \"")+object_name+'"';
}


/*:19*/
#line 580 "./pp3.w"

else
/*20:*/
#line 960 "./pp3.w"

if(opcode=="set"){
string param_name;
script>>param_name;
if(param_name=="center_rectascension")
script>>params.center_rectascension;
else if(param_name=="center_declination")
script>>params.center_declination;
else if(param_name=="box_width")
script>>params.view_frame_width;
else if(param_name=="box_height")
script>>params.view_frame_height;
else if(param_name=="grad_per_cm")
script>>params.grad_per_cm;
else if(param_name=="constellation")
params.constellation= read_string(script);
else if(param_name=="shortest_constellation_line")
script>>params.shortest_constellation_line;
else if(param_name=="label_skip")
script>>params.label_skip;
else if(param_name=="minimal_nebula_radius")
script>>params.minimal_nebula_radius;
else if(param_name=="faintest_cluster_magnitude")
script>>params.faintest_cluster_magnitude;
else if(param_name=="faintest_diffuse_nebula_magnitude")
script>>params.faintest_diffuse_nebula_magnitude;
else if(param_name=="faintest_star_magnitude")
script>>params.faintest_star_magnitude;
else if(param_name=="minimal_star_radius")
script>>params.minimal_star_radius;
else if(param_name=="faintest_star_disk_magnitude")
script>>params.faintest_star_disk_magnitude;
else if(param_name=="faintest_star_with_label_magnitude")
script>>params.faintest_star_with_label_magnitude;
else if(param_name=="star_scaling")
script>>params.star_scaling;
else if(param_name=="fontsize")
script>>params.font_size;
else
throw string("Undefined \"set\" construct in input script: \"")
+param_name+'"';
}

/*:20*/
#line 582 "./pp3.w"

else throw string("Undefined opcode in input script: \"")
+opcode+'"';
script>>opcode;
}
}

/*:13*//*21:*/
#line 1011 "./pp3.w"

typedef map<int,int> index_list;

/*:21*//*23:*/
#line 1054 "./pp3.w"

bool assure_valid_catalogue_index(const int index,const index_list&catalogue,
const string catalogue_name){
if(catalogue.find(index)==catalogue.end()){
cerr<<"pp3: Warning: Invalid "<<catalogue_name<<" index: "
<<index<<".\n";
return false;
}else return true;
}

bool assure_valid_catalogue_index(const int index,
const string constellation,
map<string,index_list> &flamsteed){
bool found= true;
if(flamsteed.find(constellation)==flamsteed.end())found= false;
else if(flamsteed[constellation].find(index)==
flamsteed[constellation].end())found= false;
if(!found)cerr<<"pp3: Warning: Invalid Flamsteed number: "
<<index<<".\n";
return found;
}

bool assure_valid_catalogue_index(const int index,
const index_list&henry_draper){
if(henry_draper.find(index)==henry_draper.end()){
cerr<<"pp3: Warning: Invalid HD number: "
<<index<<".\n";
return false;
}else return true;
}

/*:23*//*24:*/
#line 1092 "./pp3.w"

void search_objects(istream&script,
index_list&ngc,index_list&ic,
index_list&messier,index_list&henry_draper,
map<string,index_list> &flamsteed,
vector<int> &found_stars,vector<int> &found_nebulae){
found_stars.clear();
found_nebulae.clear();
string catalogue_name;
int catalogue_index;
script>>catalogue_name;
while(script&&catalogue_name!=";"){
script>>catalogue_index;
if(catalogue_index<=0){
stringstream error_message;
error_message<<"Invalid index: "<<catalogue_index;
throw error_message.str();
}
if(!script)throw string("Unexpected end of input script");

if(params.nebulae_visible||
(catalogue_name!="NGC"&&catalogue_name!="IC"&&
catalogue_name!="M")){
if(catalogue_name=="NGC"){
if(assure_valid_catalogue_index(catalogue_index,ngc,"NGC"))
found_nebulae.push_back(ngc[catalogue_index]);
}else if(catalogue_name=="IC"){
if(assure_valid_catalogue_index(catalogue_index,ic,"IC"))
found_nebulae.push_back(ic[catalogue_index]);
}else if(catalogue_name=="M"){
if(assure_valid_catalogue_index(catalogue_index,messier,"M"))
found_nebulae.push_back(messier[catalogue_index]);
}else if(catalogue_name=="HD"){
if(assure_valid_catalogue_index(catalogue_index,henry_draper))
found_stars.push_back(henry_draper[catalogue_index]);
}else{
if(assure_valid_catalogue_index(catalogue_index,
catalogue_name,flamsteed))
found_stars.
push_back(flamsteed[catalogue_name][catalogue_index]);
}
}
script>>catalogue_name;
}
}

/*:24*//*25:*/
#line 1144 "./pp3.w"

view_data*identify_object(istream&script,index_list&ngc,
index_list&ic,index_list&messier,
index_list&henry_draper,
map<string,index_list> &flamsteed,
stars_list&stars,nebulae_list&nebulae){
string catalogue_name;
int catalogue_index;
script>>catalogue_name>>catalogue_index;
if(!script)throw string("Unexpected end of input script");
if(catalogue_name=="NGC"){
if(assure_valid_catalogue_index(catalogue_index,ngc,"NGC"))
return&nebulae[ngc[catalogue_index]];
}else if(catalogue_name=="IC"){
if(assure_valid_catalogue_index(catalogue_index,ic,"IC"))
return&nebulae[ic[catalogue_index]];
}else if(catalogue_name=="M"){
if(assure_valid_catalogue_index(catalogue_index,messier,"M"))
return&nebulae[messier[catalogue_index]];
}else if(catalogue_name=="HD"){
if(assure_valid_catalogue_index(catalogue_index,henry_draper))
return&stars[henry_draper[catalogue_index]];
}else{
if(assure_valid_catalogue_index(catalogue_index,
catalogue_name,flamsteed))
return&stars[flamsteed[catalogue_name][catalogue_index]];
}
return 0;
}

/*:25*//*26:*/
#line 1187 "./pp3.w"

void read_objects_and_labels(istream&script,
const dimensions_list&dimensions,
objects_list&objects,stars_list&stars,
nebulae_list&nebulae,
texts_list&texts,
flexes_list&flexes,
const transformation&mytransform,
bool included= false){
if(!params.filename_include.empty()&&!included){
ifstream included_file(params.filename_include.c_str());
/*27:*/
#line 1243 "./pp3.w"

string token;
included_file>>token;
while(included_file){
if(token[0]=='#')getline(included_file,token);
else if(token=="objects_and_labels")break;
included_file>>token;
}


/*:27*/
#line 1198 "./pp3.w"

read_objects_and_labels(included_file,dimensions,objects,stars,
nebulae,texts,flexes,mytransform,true);
}
string opcode;
script>>opcode;
if(!script)return;
/*22:*/
#line 1025 "./pp3.w"

const int max_ngc= 7840,max_ic= 5386,max_messier= 110;
index_list ngc,ic,messier;
for(int i= 0;i<nebulae.size();i++){
if(nebulae[i].ngc> 0&&nebulae[i].ngc<=max_ngc)
ngc[nebulae[i].ngc]= i;
if(nebulae[i].ic> 0&&nebulae[i].ic<=max_ic)
ic[nebulae[i].ic]= i;
if(nebulae[i].messier> 0&&nebulae[i].messier<=max_messier)
messier[nebulae[i].messier]= i;
}
index_list henry_draper;
map<string,index_list> flamsteed;
for(int i= 0;i<stars.size();i++){
if(stars[i].hd> 0)henry_draper[stars[i].hd]= i;
if(stars[i].flamsteed> 0)
flamsteed[stars[i].constellation][stars[i].flamsteed]= i;
}


/*:22*/
#line 1205 "./pp3.w"

while(script){
if(opcode[0]=='#'){
string rest_of_line;
getline(script,rest_of_line);
}else
/*28:*/
#line 1268 "./pp3.w"

if(opcode=="reposition"){
string position,semicolon;
view_data*current_object= 
identify_object(script,ngc,ic,messier,henry_draper,
flamsteed,stars,nebulae);
int angle;
bool on_baseline= false;
script>>position>>semicolon;
if(semicolon!=";")
throw string("Expected \";\" after \"reposition\" command");
/*29:*/
#line 1289 "./pp3.w"

if(position=="E"||position=="E_")angle= 0;
else if(position=="NE")angle= 1;
else if(position=="N")angle= 2;
else if(position=="NW")angle= 3;
else if(position=="W"||position=="W_")angle= 4;
else if(position=="SW")angle= 5;
else if(position=="S")angle= 6;
else if(position=="SE")angle= 7;
else throw string("Undefined position angle: ")+position;
on_baseline= position[position.length()-1]=='_';


/*:29*/
#line 1280 "./pp3.w"

if(current_object){
current_object->label_angle= angle;
current_object->with_label= visible;
current_object->on_baseline= on_baseline;
current_object->label_arranged= true;
}
}

/*:28*/
#line 1211 "./pp3.w"

else
/*30:*/
#line 1306 "./pp3.w"

if(opcode=="set_label_text"){
view_data*current_object= 
identify_object(script,ngc,ic,messier,henry_draper,
flamsteed,stars,nebulae);
if(current_object)current_object->label= read_string(script);
}


/*:30*/
#line 1213 "./pp3.w"

else
/*35:*/
#line 1422 "./pp3.w"

if(opcode=="text"){
string token,contents,position("NE");
double rectascension,declination;
contents= read_string(script);
script>>token;
if(token!="at")throw string("\"at\" in \"text\" command expected");
script>>rectascension>>declination;
script>>token;
int angle= 1;
bool on_baseline= false;
enum{kind_text_label,kind_flex_declination}label_kind
= kind_text_label;
double step_rectascension= -1.0;
double step_declination= -1.0;
while(script&&token!=";"){
if(token=="color")script>>params.textlabelcolor;
else if(token=="towards"){
script>>position;
/*29:*/
#line 1289 "./pp3.w"

if(position=="E"||position=="E_")angle= 0;
else if(position=="NE")angle= 1;
else if(position=="N")angle= 2;
else if(position=="NW")angle= 3;
else if(position=="W"||position=="W_")angle= 4;
else if(position=="SW")angle= 5;
else if(position=="S")angle= 6;
else if(position=="SE")angle= 7;
else throw string("Undefined position angle: ")+position;
on_baseline= position[position.length()-1]=='_';


/*:29*/
#line 1442 "./pp3.w"

}
else if(token=="along"){
script>>token;
if(token=="declination"){
label_kind= kind_flex_declination;
}else throw string("Invalid \"along\" option");
}
else if(token=="tics"){
script>>token;
if(token=="rectascension"){
script>>step_rectascension;
if(step_rectascension<=0.0)
throw string("Invalid \"tics\" interval");
step_declination= -1.0;
}else if(token=="declination"){
script>>step_declination;
if(step_declination<=0.0)
throw string("Invalid \"tics\" interval");
step_rectascension= -1.0;
}else throw string("Invalid \"tics\" option");
}else throw string("Invalid \"text\" option");
script>>token;
}
if(!script)
throw string("Unexpected end of script while scanning \"text\"");
if(step_rectascension<=0.0&&step_declination<=0.0){
/*36:*/
#line 1494 "./pp3.w"

switch(label_kind){
case kind_text_label:
texts.push_back(text(contents,rectascension,declination,
params.textlabelcolor,angle,on_baseline));
break;
case kind_flex_declination:
flexes.push_back(new declination_flex(contents,rectascension,
declination,
params.textlabelcolor,angle,
on_baseline));
break;
}

/*:36*/
#line 1469 "./pp3.w"

}if(step_rectascension> 0.0){
string user_pattern(contents);
double start= rectascension-floor(rectascension/step_rectascension)
*step_rectascension;
for(rectascension= start;rectascension<24.0;
rectascension+= step_rectascension){cerr<<rectascension<<' ';
/*37:*/
#line 1521 "./pp3.w"

{
stringstream coordinates;
coordinates.setf(ios::fixed);
coordinates<<"\\def\\coordinates#1#2#3#4#5#6#7#8#9{\\TicMark{"
<<user_pattern<<"}}";
coordinates<<"\\coordinates{"<<rectascension<<"}{"
<<declination<<"}{";
coordinates<<int(floor(rectascension))<<"}{"
<<int(floor((rectascension-floor(rectascension))
*60.0))
<<"}{";
if(int(declination)> 0.0)coordinates<<'+';
coordinates<<int(declination)<<"}{}{}{}{}";
contents= coordinates.str();
while(contents.find(".")!=string::npos)
contents.replace(contents.find("."),1,"{\\DP}");
}

/*:37*/
#line 1476 "./pp3.w"

/*36:*/
#line 1494 "./pp3.w"

switch(label_kind){
case kind_text_label:
texts.push_back(text(contents,rectascension,declination,
params.textlabelcolor,angle,on_baseline));
break;
case kind_flex_declination:
flexes.push_back(new declination_flex(contents,rectascension,
declination,
params.textlabelcolor,angle,
on_baseline));
break;
}

/*:36*/
#line 1477 "./pp3.w"

}
}else if(step_declination> 0.0){
string user_pattern(contents);
double start= declination-floor((declination+90.0)/step_declination)
*step_declination;
for(declination= start;declination<=90.0;
declination+= step_declination){cerr<<declination<<' ';
/*37:*/
#line 1521 "./pp3.w"

{
stringstream coordinates;
coordinates.setf(ios::fixed);
coordinates<<"\\def\\coordinates#1#2#3#4#5#6#7#8#9{\\TicMark{"
<<user_pattern<<"}}";
coordinates<<"\\coordinates{"<<rectascension<<"}{"
<<declination<<"}{";
coordinates<<int(floor(rectascension))<<"}{"
<<int(floor((rectascension-floor(rectascension))
*60.0))
<<"}{";
if(int(declination)> 0.0)coordinates<<'+';
coordinates<<int(declination)<<"}{}{}{}{}";
contents= coordinates.str();
while(contents.find(".")!=string::npos)
contents.replace(contents.find("."),1,"{\\DP}");
}

/*:37*/
#line 1485 "./pp3.w"

/*36:*/
#line 1494 "./pp3.w"

switch(label_kind){
case kind_text_label:
texts.push_back(text(contents,rectascension,declination,
params.textlabelcolor,angle,on_baseline));
break;
case kind_flex_declination:
flexes.push_back(new declination_flex(contents,rectascension,
declination,
params.textlabelcolor,angle,
on_baseline));
break;
}

/*:36*/
#line 1486 "./pp3.w"

}
}
}

/*:35*/
#line 1215 "./pp3.w"

else{
vector<int> found_stars,found_nebulae;
/*31:*/
#line 1318 "./pp3.w"

if(opcode=="delete_labels"){
search_objects(script,ngc,ic,messier,henry_draper,
flamsteed,found_stars,found_nebulae);
for(int i= 0;i<found_stars.size();i++){
stars[found_stars[i]].with_label= hidden;
stars[found_stars[i]].label_arranged= true;
}
for(int i= 0;i<found_nebulae.size();i++){
nebulae[found_nebulae[i]].with_label= hidden;
nebulae[found_nebulae[i]].label_arranged= false;
}
}

/*:31*/
#line 1218 "./pp3.w"

else
/*32:*/
#line 1336 "./pp3.w"

if(opcode=="add_labels"){
search_objects(script,ngc,ic,messier,henry_draper,
flamsteed,found_stars,found_nebulae);
for(int i= 0;i<found_stars.size();i++)
stars[found_stars[i]].with_label= visible;
for(int i= 0;i<found_nebulae.size();i++)
nebulae[found_nebulae[i]].with_label= visible;
}

/*:32*/
#line 1220 "./pp3.w"

else
/*34:*/
#line 1361 "./pp3.w"

if(opcode=="delete"){
search_objects(script,ngc,ic,messier,henry_draper,
flamsteed,found_stars,found_nebulae);
for(int i= 0;i<found_stars.size();i++)
stars[found_stars[i]].in_view= hidden;
for(int i= 0;i<found_nebulae.size();i++)
nebulae[found_nebulae[i]].in_view= hidden;
}

/*:34*/
#line 1222 "./pp3.w"

else
/*33:*/
#line 1349 "./pp3.w"

if(opcode=="add"){
search_objects(script,ngc,ic,messier,henry_draper,
flamsteed,found_stars,found_nebulae);
for(int i= 0;i<found_stars.size();i++)
stars[found_stars[i]].in_view= visible;
for(int i= 0;i<found_nebulae.size();i++)
nebulae[found_nebulae[i]].in_view= visible;
}

/*:33*/
#line 1224 "./pp3.w"

else throw string("Undefined opcode in input script: \"")
+opcode+'"';
}
script>>opcode;
}
}

/*:26*/
#line 3852 "./pp3.w"


int main(int argc,char**argv){
try{
/*118:*/
#line 3901 "./pp3.w"

if(argc==2){
if(argv[1][0]!='-'){
params.in= new ifstream(argv[1]);
if(!params.in->good())
throw string("Input script file ")+argv[1]
+" not found";
else params.input_file= true;
}else if(!strcmp(argv[1],"-"))params.in= &cin;else
cerr<<"Invalid argument: "<<argv[1]<<endl;
}
if(params.in==0){
cerr<<"PP3 1.3.2  Copyright (c) 2002--2004 Torsten Bronger\n"
<<"           http://pp3.sourceforge.net\n\n"
<<"Syntax:\n  pp3 {input-file}\n\n"
<<"{input-file} may be \"-\" to denote standard input.\n"
<<"You may give an empty file to get a default plot.\n"
<<"The plot is sent to standard output by default.\n";
exit(0);
}

/*:118*/
#line 3856 "./pp3.w"

read_parameters_from_script(*params.in);
if(!params.filename_output.empty())
params.out= new ofstream(params.filename_output.c_str());
transformation mytransform(params.center_rectascension,
params.center_declination,
params.view_frame_width,
params.view_frame_height,
params.grad_per_cm);

/*119:*/
#line 3925 "./pp3.w"

boundaries_list boundaries;
dimensions_list dimensions;
objects_list objects;
stars_list stars;
nebulae_list nebulae;
connections_list connections;
texts_list texts;
flexes_list flexes;

read_stars(stars);

if(params.show_boundaries)read_constellation_boundaries(boundaries);
read_label_dimensions(dimensions);
if(params.nebulae_visible)read_nebulae(nebulae);
if(params.show_lines)read_constellation_lines(connections,stars);

/*:119*/
#line 3866 "./pp3.w"


read_objects_and_labels(*params.in,dimensions,objects,stars,
nebulae,texts,flexes,mytransform);

OUT.setf(ios::fixed);
OUT.precision(3);
/*121:*/
#line 3971 "./pp3.w"

create_preamble(OUT);
OUT<<"\\usepackage[nohead,nofoot,margin=0cm,"
<<"paperwidth="<<params.view_frame_width_in_bp()<<"bp,"
<<"paperheight="<<params.view_frame_height_in_bp()<<"bp"
<<"]{geometry}\n\n"
<<"\n\\begin{document}\\parindent0pt\n"
<<"\\pagestyle{empty}\\thispagestyle{empty}%\n"
<<"\\special{papersize="<<params.view_frame_width_in_bp()-0.1
<<"bp,"<<params.view_frame_height_in_bp()-0.1<<"bp}%\n"
<<"\\vbox to "<<params.view_frame_height_in_bp()<<"bp{"
<<"\\vfill"
<<"\\hbox to "<<params.view_frame_width_in_bp()<<"bp{%\n"
<<params.bgcolor<<params.gridcolor<<params.eclipticcolor<<params.horizoncolor
<<params.boundarycolor<<params.hlboundarycolor<<params.starcolor
<<params.nebulacolor<<params.clinecolor;

/*:121*/
#line 3873 "./pp3.w"

OUT<<"\\psclip{\\psframe[linestyle=none](0bp,0bp)("
<<params.view_frame_width_in_bp()
<<"bp,"<<params.view_frame_height_in_bp()<<"bp)}%\n"
<<"\\psframe*[linecolor=bgcolor,linestyle=none](-1bp,-1bp)("
<<params.view_frame_width_in_bp()+1
<<"bp,"<<params.view_frame_height_in_bp()+1<<"bp)%\n";
/*120:*/
#line 3949 "./pp3.w"

if(params.milkyway_visible)draw_milky_way(mytransform);
create_grid(mytransform);
if(params.show_boundaries)
draw_boundaries(mytransform,boundaries,objects,
params.constellation);
draw_flex_labels(mytransform,flexes,objects,dimensions);
draw_text_labels(mytransform,texts,objects);
if(params.nebulae_visible)draw_nebulae(mytransform,nebulae,objects);
draw_stars(mytransform,stars,objects);
if(params.show_lines)
draw_constellation_lines(connections,stars,objects);
if(params.show_labels){
arrange_labels(objects,dimensions);
print_labels(objects);
}

/*:120*/
#line 3880 "./pp3.w"

OUT<<"\\endpsclip\n";
/*123:*/
#line 4063 "./pp3.w"

OUT<<"\\hfill}}\\end{document}\n";

/*:123*/
#line 3882 "./pp3.w"

if(params.input_file)delete params.in;
if(!params.filename_output.empty())
delete params.out;else OUT.flush();
/*124:*/
#line 4069 "./pp3.w"

if(!params.filename_output.empty()&&(params.create_eps
||params.create_pdf)){
string commandline= string("latex ")+params.filename_output;
if(system(commandline.c_str())==0){
string base_filename(params.filename_output);
if(base_filename.find('.')!=string::npos)
base_filename.erase(base_filename.find('.'));
commandline= string("dvips -o ")+base_filename+".eps "
+base_filename;
if(system(commandline.c_str())==0){
if(params.create_pdf){
commandline= string("ps2pdf ")+
"-dCompatibility=1.3 "+
base_filename+".eps "+base_filename+".pdf";
if(system(commandline.c_str())!=0)
throw string("ps2pdf call failed: ")+commandline;
}
}else throw string("dvips call failed: ")+commandline;
}else throw string("LaTeX call failed: ")+commandline;
}


/*:124*/
#line 3886 "./pp3.w"

}
catch(string s){
cerr<<"pp3: "<<s<<'.'<<endl;
exit(1);
}
return 0;
}

/*:117*/
