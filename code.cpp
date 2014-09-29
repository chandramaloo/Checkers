// PROJECT SUBMISSION BY CHANDRA MALOO(130050009) AND PARTH SHAH(130050015)
#include <simplecpp> 
int hx[4],hy[4];												//storing positions of highlight
int p[8][8],k;
float f=0.5;													//creating a virtual board
int xco[2], yco[2], xhco[3], yhco[3]; 							//storing positions of selection 
bool chance=true,exit=false,begin=true,newgame=false,instru=false,multiplekill=false,killmade=false,chanceh,undo=false;	
																//chance : decides the player
																//exit : decides the exit status
																//begin : checks for game begining
																//newgame : end of one game 
																//kill made : checks for kill move;
																//multiple kill : checks for possibility of multiple kill
string winner;													// stores winners name
int click=1; 													// checks for the click name
void find_box(double x , double y , int &a , int &b) 			// find box according to click
{	for(int i=1 ; i <= 8 ; i+=1)
	{	for(int j=1 ; j <= 8 ; j+=1)
		{	if(x/f >= 100*i-50 && x/f <= 100*(i+1)-50 && y/f <= 100*(j+1)-50 && y/f >= 100*j-50)// -50 becoz of grid selection
			{	a=i; 			
				b=j;
			}
		}
	}
}

void highlight(int i, int j, int size) 							// used in printing/enlarging of piece
{	Circle c(i*100*f,j*100*f, size*f);
	int r,g,b;
	c.setFill(true);
	if(chance){r=255;g=b=0;}									//colour selection 
	else r=g=b=0;
	c.setColor(COLOR(r,g,b));
	c.imprint();
	if(p[j-1][i-1]==31 || p[j-1][i-1]==32){  					//to create difference for king 
		c.show();
		c.reset(i*100*f,j*100*f,20*f);	
		c.setColor(COLOR(255,255,255));
		c.imprint();
		c.hide();
	}
	c.hide();
}

void invisible(int i, int j)   									// makes piece invisible 
{	Rectangle r(i*100*f,j*100*f,100*f,100*f);
	r.setFill(true);
	r.setColor(COLOR(200,200,200));
	r.imprint();
	r.hide();
}
			
class checkers{
	public:
	bool initial(int i, int j){									// checks for legitimacy of initial selection 
		if(chance==true && (p[j-1][i-1]==1 || p[j-1][i-1]==31) ) return true;
		else if(chance==false && (p[j-1][i-1]==2 || p[j-1][i-1]==32) ) return true;
		else return false;
	}
	
	bool normalmove(int i, int j, int c){ 						// checks for condition of normal move
		if( i > 8 || i <= 0 || j <= 0 || j > 8)return false;
		
		if(initial(i , j) && c==1 && multiplekill == false){
				invisible(xco[0],yco[0]);
				highlight(xco[0],yco[0],30);
				xco[0]=i; yco[0]=j; 							//case where player changes his selection
				rempossible();
				showpossible(xco[0],yco[0]);
				highlight(xco[0],yco[0],35);
				return false;
		}
		
		if(p[j-1][i-1]!=0)return false; 						// checking whether place is empty or not
		
		if(pow(i-xco[0],2)==1 && pow(j-yco[0],2)==1) 			//checking diagonal movement
			if((chance==true && j-yco[0]>0)||(chance==false && j-yco[0]<0)||(p[yco[0]-1][xco[0]-1]==31)||(p[yco[0]-1][xco[0]-1]==32))  													// checking correct direction of movt and king condition
				return true;
				
		return false;
	}
	
	bool killmove(int i, int j, int c){ 						// checks for condition of kill move
		if( i > 8 || i <= 0 || j <= 0 || j > 8)return false;
		
		if(initial(i , j) && c==1 && multiplekill == false){
				invisible(xco[0],yco[0]);
				highlight(xco[0],yco[0],30);
				xco[0]=i; yco[0]=j; 							//case where player changes his selection
				rempossible();
				showpossible(xco[0],yco[0]);
				highlight(xco[0],yco[0],35);
				return false;
		}
		
		if(p[j-1][i-1]!=0){
			return false; 										// checking whether place is empty or not
		}
		
		if(pow(i-xco[0],2)==4 && pow(j-yco[0],2)==4){			// checks for killing move
			if( (chance == true && ( p[ (yco[0]+j)/2 - 1][ (xco[0]+i)/2 - 1] == 2 || p[ (yco[0]+j)/2 - 1][ (xco[0]+i)/2 - 1] == 32 ) ) || 	(chance == false && ( p[ (yco[0]+j)/2 - 1][ (xco[0]+i)/2 - 1] == 1 || p[ (yco[0]+j)/2 - 1 ][ (xco[0]+i)/2 - 1] == 31) ))	
				if((chance==true && j-yco[0]>0)||(chance==false && j-yco[0]<0)||(p[yco[0]-1][xco[0]-1]==31)||(p[yco[0]-1][xco[0]-1]==32)){
					return true;
				}
		}
		return false;
	}
	
	void showpossible(int i,int j){ 							// highlights the possible places for piece movement
		int count=0;bool kill = false;
		hx[0]=hx[1]=hx[2]=hx[3]=hy[0]=hy[1]=hy[2]=hy[3]=0;
		for (int x=i-2; x<=i+2; x+=4){ 							// checks if possible kill move is there or not
			for (int y=j-2; y<=j+2; y+=4){
				if(killmove(x,y,0)){
					kill = true;
					hx[count]=x;hy[count]=y;
					count++;
				}					
			}
		}
		if(kill == false){ 										// if kill is there then does not highlight the normal moves
			for (int x=i-1; x<=i+1; x++){
				for (int y=j-1; y<=j+1; y++){
					if(normalmove(x,y,0)){
						hx[count]=x;hy[count]=y;
						count++;
					}					
				}
			}	
		}
		for(int i=0 ; i < 4 ; i++){ 							// highlighting the positions
			if(hx[i] !=0 ){
					Rectangle r(hx[i]*100*f,hy[i]*100*f,100*f,100*f);
					r.setFill(true);
					r.setColor(COLOR(255,255,40));
					r.imprint();
					r.hide();
			}			
		}
	}

	void rempossible(){ 										// removes the shown higlighted places
		for(int i=0; i < 4; i++){
			if(hx[i] != 0 && hy[i] != 0){
				Rectangle r(hx[i]*100*f,hy[i]*100*f,100*f,100*f);
				r.setFill(true);
				r.setColor(COLOR(200,200,200));
				r.imprint();
				r.hide();
			}
		}
		hx[0]=hx[1]=hy[0]=hy[1]=-100;
	}
	
	void move_end(int i1, int j1, int i2, int j2) 				// does all changes at the end of a turn
	{	invisible(i1,j1);										// removes piece from initial position
		Circle c(i2*100*f,j2*100*f,30*f); 							// creating piece at new position
		c.setFill(true);	
		int r,g,b;
		if(chance){r=255;g=b=0;}
		else r=g=b=0;
		c.setColor(COLOR(r,g,b));
		c.imprint();
		c.hide();
		p[yco[1]-1][xco[1]-1]=p[yco[0]-1][xco[0]-1];			//changing virtual board:at new location
		p[yco[0]-1][xco[0]-1]=0;								//changing virtual board:updating old
		if(abs(yco[1]-yco[0])==2){ 								// for killing move
			k=p[(yco[0]+yco[1])/2-1][(xco[0]+xco[1])/2-1];
			p[(yco[0]+yco[1])/2-1][(xco[0]+xco[1])/2-1]=0;
			invisible((xco[0]+xco[1])/2,(yco[0]+yco[1])/2);	
		}
		if(chance==true){
			if(yco[1]==8){
				p[yco[1]-1][xco[1]-1]=31; 						// 3 indicates king 1 indicates player
			}
		}
		else if(yco[1]==1){
			p[yco[1]-1][xco[1]-1]=32;							// 3 indicates king 2 indicates player
		}
		if(p[yco[1]-1][xco[1]-1]==31 || p[yco[1]-1][xco[1]-1]==32){ // changing animation for king
			c.show();
			c.reset(i2*100*f,j2*100*f,20*f);
			c.setColor(COLOR(255,255,255));
			c.imprint();
			c.hide();
		}
	
		multiplekill=killmade=false;					 		// initialising the 2 variables
		
		if(abs(xco[1]-xco[0])==2)killmade=true; 				// checking kill made
		
		xco[0]=xco[1]; yco[0]=yco[1];
		if(killmade == true){									// checking for multiple kill 
			for (int x=xco[0]-2; x<=xco[0]+2; x+=4){
				for (int y=yco[0]-2; y<=yco[0]+2; y+=4){
					if(killmove(x,y,0)){
					multiplekill = true;
					click++;
					highlight(xco[0],yco[0],35);
					showpossible(xco[0],yco[0]);
					break;
					}					
				}
			}
		}
		if( killmade == true ){
			if( multiplekill == false ) chance=!chance; 		//condition when to change chance
		}
		else {
			chance = !chance;
			killmade = multiplekill = false; 					//condition when to change chance
		}
	}

	bool gamewin(){ 											// checking gamewin
	//game end when a player has no piece remaining or has no legitimate move
		if(multiplekill==true)return false;
		bool win2=true;
		bool win1=true;	
		if(chance == true){ 
			win1=false; 
			for(int i=0; i<8; i++){ 
				for(int j=0; j<8; j++) {
					if(p[j][i]==1 || p[j][i]==31){
						xco[0]=i+1;yco[0]=j+1;
						for (int x=xco[0]-2; x<=xco[0]+2; x++){
							for (int y=yco[0]-2; y<=yco[0]+2; y++){
								win2=!(killmove(x,y,0)||normalmove(x,y,0)); // checks if pieces have a legitimate move or not
								if(win2==false)break;
							}
							if(win2==false)break;
						}
						if(win2==false)break;
					}
				}
				if(win2==false)break;
			}
		}
		else{
			win2=false;
			for(int i=0; i<8; i++){ 
				for(int j=0; j<8; j++) {
					if(p[j][i]==2 || p[j][i]==32){
						xco[0]=i+1;yco[0]=j+1;
						for (int x=i-2; x<=i+2; x++){
							for (int y=j-2; y<=j+2; y++){
								win1=!(killmove(x,y,0)||normalmove(x,y,0)); // checks if pieces have a legitimate move or not
								if(win1==false)break;
							}
							if(win1==false)break;
						}
						if(win1==false)break;
					}
				}
				if(win1==false)break;
			}
		}
		if(win1 || win2){
			Rectangle r(1125/2*f,450*f,2500*f,2000*f);
			r.setFill(true);
			r.setColor(COLOR(255,255,255));
			r.imprint();
			r.hide();
			if(win1) { Text t(550*f,450*f,"Player 1 wins !"); wait(5);t.hide();}
			else { Text t(550*f,450*f,"Player 2 wins !"); wait(5);t.hide();}
		}
	xco[0]=yco[0]=0;
	return win1 || win2 ;
	
	}
	void undoch(){
		undo = false;
		if(click % 2 == 0 ){ // to undo when incidentally a wrong move is played
			invisible(xco[0],yco[0]);
			highlight(xco[0],yco[0],30);
			rempossible();
			click--;
		}
		if(xhco[2] != 0 ){
			highlight(xhco[2],yhco[2],30);
			p[yhco[2]-1][xhco[2]-1]=k;
		}
		chance=chanceh;
		p[yhco[0]-1][xhco[0]-1]=p[yhco[1]-1][xhco[1]-1];
		p[yhco[1]-1][xhco[1]-1]=0;
		invisible(xhco[1],yhco[1]);
		highlight(xhco[0],yhco[0],30);
	}	
};

				
main_program
{   initCanvas("Checkers",1125*f,900*f);	
	new_game:	
	// Creating interface
	Text t1(550*f,225*f,"WELCOME TO CHECKERS");	
	if(newgame==true)Text t2(550*f,250*f,winner+" wins");
	Circle c(400*f,450*f,75*f); 										// creating action buttons
	c.setFill(true);
	c.setColor(COLOR(0,0,255));
	c.imprint();
	c.reset(725*f,450*f,75*f);
	c.setFill(true);	
	c.setColor(COLOR(255,0,0));
	c.imprint();
	c.reset(562.5*f,450*f,75*f);
	c.setColor(COLOR(0,255,0));
	c.imprint();
	c.hide();
	Turtle t;
	t.penUp();
	t.forward(-180*f);
	t.scale(2.5*f);
	t.setColor(COLOR(255,255,255));
	t.imprint();
	t.hide();	
	Rectangle r(562.5*f,450*f,80*f,20*f);
	r.setFill(true);
	r.setColor(COLOR(255,255,255));
	r.imprint();
	r.move(0,30*f);
	r.imprint();
	r.move(0,-60*f);
	r.imprint();
	r.reset(725*f,450*f,100*f,20*f);
	r.left(45);
	r.imprint();
	r.left(90);
	r.imprint();
	r.hide();
	
	XEvent event1;
	while (true){
		nextEvent(&event1);
		if(mouseButtonPressEvent(&event1) && event1.xbutton.button==1){ // checking for the player response at the beginning
			int x=event1.xbutton.x;
		    int y=event1.xbutton.y;
			if( ((x-400*f)*(x-400*f)+(y-450*f)*(y-450*f)) <= 75*75*f*f ) { break; }
			if( ((x-562.5*f)*(x-562.5*f)+(y-450*f)*(y-450*f)) <= 75*75*f*f ) { instru=true; goto instru; break; }
			if( ((x-725*f)*(x-725*f)+(y-450*f)*(y-450*f)) <= 75*75*f*f ) { exit=true; break; } 
		}
	}
	
	instru: // mark for instructions
	if(instru){
		r.show();
		r.reset(550*f,450*f,2500*f,2000*f);
		r.imprint();
		instru=false;
		t1.reset(500*f,100*f,"INSTRUCTIONS");t1.imprint();
		t1.reset(304*f,200*f,"1. Checkers is played by two players. Each player begins the game with 12 colored pieces.");t1.imprint();
		t1.reset(294*f,225*f,"2. The board consists of 64 squares, alternating between 32 dark and 32 light squares.");t1.imprint();
		t1.reset(247*f,250*f,"3. The pieces are placed on the 12 dark squares closest to the player.");t1.imprint();
		t1.reset(276*f,275*f,"4. Moves are allowed only on the dark squares, so pieces always move diagonally.");t1.imprint();
		t1.reset(261*f,300*f,"5. Single pieces are always limited to forward moves (toward the opponent).");t1.imprint();
		t1.reset(381*f,325*f,"6. When a piece reaches the furthest row from the player who controls that piece, it is crowned and becomes a king.");t1.imprint();
		t1.reset(290*f,350*f,"7. Kings are also limited to move diagonally, but may move both forward and backward.");t1.imprint();
		t1.reset(453*f,375*f,"8. A piece making a capturing move (a jump) leaps over one of the opponent's pieces, landing in a straight diagonal line on the other side.");t1.imprint();
		t1.reset(443*f,400*f,"9. Only one piece may be captured in a single jump; however, multiple jumps are allowed on a single turn and if possible should be done.");t1.imprint();
		t1.reset(211*f,425*f,"10. When a piece is captured, it is removed from the board.");t1.imprint();
		t1.reset(213*f,450*f,"11. In case a piece has a killing move it should take that.");t1.imprint();
		t1.reset(282*f,475*f,"12. The game ends when a player has no piece remaining or has no legitimate moves.");t1.imprint();
		t1.reset(1000*f,100*f,"BACK");
		r.reset(1000*f,100*f,50*f,20*f);
		r.setFill(false);
		r.imprint();
		while (true){
			nextEvent(&event1);
			if(mouseButtonPressEvent(&event1) && event1.xbutton.button==1){ // checking for starting game
				int x=event1.xbutton.x;
		    	int y=event1.xbutton.y;
				if( x > 975*f && x < 1025*f && y > 90*f && y < 110*f ) {
					r.reset(550*f,450*f,1100*f,900*f);
					r.setFill(true);
					r.setColor(COLOR(255,255,255));
					r.imprint();r.hide();
					goto new_game;
				}
			}
		}
	}
		
	while(!exit){ // checking for exit status
		chance =true;		
		t1.hide();
		r.show();
		r.reset(550*f,450*f,1100*f,900*f);
		r.imprint();
		r.hide();
	
		bool comp=false; 		//true means chance has ended
		double x , y ;
		
		for(int i=0; i<8; i++) for(int j=0; j<8; j++) p[i][j]=0;	//filling the virtual board
		for(int j=0; j<3; j++) for(int i=0; i<8; i++) if((i+j) % 2 == 0){p[j][i]=1;}
		for(int j=5; j<8; j++) for(int i=0; i<8; i++) if((i+j) % 2 == 0){p[j][i]=2;}	
		for(int j=0; j<8; j++) for(int i=0; i<8; i++) if((i+j) % 2 == 0)invisible(i+1,j+1);
		for(int j=1; j<=8; j++) for(int i=1; i<=8; i++) if((i+j) % 2 != 0){
			Rectangle r2(i*100*f,j*100*f,100*f,100*f);
			r2.setFill(false);
			r2.imprint();
			r2.hide();
		}   
		checkers pl;
		
	
		// creating initial setup of coins
		c.reset(100*f,100*f,30*f);c.setFill(true);
		c.setColor(COLOR(255,0,0));//placing the red coins
		repeat(4){c.imprint();c.move(200*f,0);}c.move(-700*f,100*f);
		repeat(4){c.imprint();c.move(200*f,0);}c.move(-900*f,100*f);
		repeat(4){c.imprint();c.move(200*f,0);}
		c.setColor(COLOR(0,0,0));c.move(-700*f,300*f);//placing the black coins
		repeat(4){c.imprint();c.move(200*f,0);}c.move(-900*f,100*f);
		repeat(4){c.imprint();c.move(200*f,0);}c.move(-700*f,100*f);	
		repeat(4){c.imprint();c.move(200*f,0);}
	
		c.setColor(COLOR(0,0,0));
		c.reset(925*f,100*f,50*f);
		c.imprint();
		c.move(125*f,0);
		c.setColor(COLOR(255,0,0));
		c.imprint();
		c.reset(1000*f,500*f,20*f);
		c.setColor(COLOR(0,0,255));
		c.imprint();
		c.hide();
		Text t0(1000*f,550*f,"Undo");t0.imprint();t0.hide();
		r.show();
		r.reset(1050*f,100*f,70*f,15*f);
		r.setFill(true);
		r.setColor(COLOR(255,255,255));
		r.left(45);
		r.imprint();
		r.left(90);
		r.imprint();
		r.reset(925*f,100*f,50*f,50*f);
		r.setColor(COLOR(255,255,255));
		r.imprint();
		r.hide();
			
		    XEvent event;
			while(true){	// beginning of the game
				if(begin==true){begin=false;}
				beginning:
				Text t1(450*f,25*f,"PLAYER 1");t1.imprint();t1.hide(); // printing the information
				Text t2(450*f,975*f,"PLAYER 2");t2.imprint();t2.hide();
				r.show();r.reset(950*f,450*f,100*f,50*f);r.imprint();r.hide();
				if(chance){
					Text t3(1000*f,450*f,"Player 1's turn");t3.imprint();t3.hide();
					goto prog;
				}
				else if(chance==false){
					Text t3(1000*f,450*f,"Player 2's turn");t3.imprint();t3.hide();
					goto prog;
				}
			
				prog: // mark for beginning of a turn
				while(true)
				{	
					nextEvent(&event); // checks for runtime restart or exit possibility
			 		if(mouseButtonPressEvent(&event) && event.xbutton.button==1){
				    	x=event.xbutton.x;
				    	y=event.xbutton.y;
						if( ((x-925*f)*(x-925*f)+(y-100*f)*(y-100*f)) <= 50*50*f*f ) {begin=true;break;}
						if( ((x-1050*f)*(x-1050*f)+(y-100*f)*(y-100*f)) <= 50*50*f*f ) {exit=true;break;}
						if( ((x-1000*f)*(x-1000*f)+(y-500*f)*(y-500*f)) <= 20*20*f*f && undo) {pl.undoch();goto beginning;break;}
					}
			 		if(mouseButtonPressEvent(&event) && event.xbutton.button==1 && click % 2 != 0)//takes initial click of a turn 
					{ 		
						x=event.xbutton.x;
				    	y=event.xbutton.y;
				    	find_box(x,y,xco[0],yco[0]); // to find the box where player clicked 
				        if( !pl.initial(xco[0], yco[0]) )continue;// checking legitimate selection
				        highlight(xco[0],yco[0],35);// highlight selected piece
				        pl.showpossible(xco[0],yco[0]);// show possible places for movement
				        click++;
				    }
				    else if (mouseButtonPressEvent(&event) && event.xbutton.button==1)//takes final click of a turn
					{      	
						x=event.xbutton.x;
				    	y=event.xbutton.y;
				        find_box(x,y,xco[1],yco[1]); // to find the box where player clicked 
				        bool kill,normal,killpos;
				        kill = normal = killpos = false; 
				     	for (int x=xco[0]-2; x<=xco[0]+2; x+=4){ // checks if killing move possible
							for (int y=yco[0]-2; y<=yco[0]+2; y+=4){
								if(pl.killmove(x,y,0)){
									killpos=true;
								}					
							}
						}
				        kill = pl.killmove(xco[1],yco[1],1);
				        if(killpos == false) normal = pl.normalmove(xco[1],yco[1],1);// if kill possible ignores normal move
				        if ( !(kill || normal) ) continue;// checking legitimate selection
				        click++;
				        comp=true;
				        invisible(xco[0],yco[0]);
						pl.rempossible();
						undo=true;
						for(int i=0; i<2; i++){ 								//storing history
							xhco[i] = xco[i];	yhco[i] = yco[i];
						}
						chanceh=chance;
						if(abs(xco[1]-xco[0])==2){
							xhco[2]=(xco[1]+xco[0])/2;
							yhco[2]=(yco[1]+yco[0])/2;
						}
						else{
							xhco[2]=0;
							yhco[2]=0;
						}
					}
				    
					if(click % 2 !=0 && comp == true){
						pl.move_end(xco[0] , yco[0] , xco[1] , yco[1]);// calling move end fn
						comp=false;				 
						bool end = pl.gamewin();
						if(end==true){goto new_game;break;}
				    	break;
				    }
				    
				} //inner while 
				if(exit || begin || newgame)break;
			}// outer main while
	}      
}
