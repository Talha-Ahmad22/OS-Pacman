#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define NUM_THREADS 2

struct Object {
    Sprite sp;
    Texture tex;
    // Add any other data members as needed
};
 Sprite gpower[2];
  Sprite food[60],pallets[4];
 pthread_t  pacman, g[4];
 Object obj[15];
 Object pac, ghost[4];
 Texture gp;
 int x=0,y=0;
 int count=0;
 int lives=3;
 Texture f;
 bool check=false;
 int tm=0;
 Clock cl,cl1;
 int manage=0;
 bool both[4]{false};
 int permit=2;
 int key2=2;
 int score=0;
 bool gkey[4]{false};
 bool gpermit[4]{false};
 bool temp=false;
// bool WallCheck(Sprite a){


// // Assuming you have a function to get the walls' boundaries
// sf::FloatRect wallBoundaries = getWallBoundaries(); 

// sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

// }

// }
void palletIntersect(){
     if(check==false){
    for(int i=0;i<4;i++){
     if(pallets[i].getGlobalBounds().intersects(pac.sp.getGlobalBounds())){
                cl.restart();
               check=true;
              pallets[i].move(-100,-100);
    }   
    } 

    }



} 
bool ghostIntersect(Sprite s){
      for(int i=0;i<14;i++){
        if(obj[i].sp.getGlobalBounds().intersects(s.getGlobalBounds())){
              return true;
        }
           
    }
   return false;

}
bool intersect(){
    
    for(int i=0;i<14;i++){
        if(obj[i].sp.getGlobalBounds().intersects(pac.sp.getGlobalBounds())){
              return true;
        }
           
    }
   return false;

}
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore,s,gh[4],ga,mg;
bool game_finished = false;
int key=0;
int shared_variable = 0;
float x1=0,x2=0,x3=0,x4=0;
float y1=-0.1,y2=-0.1,y3=-0.1,y4=-0.1;
int x5=0,y5=0,x7=0,y7=0;
int y6=0;int x6=0,x8=0,y8=0;
float speed=1,speed1=1;
int z=0;
void* thread_function(void* arg) {
    // Lock the mutex before accessing the shared variable
    pthread_mutex_lock(&mutex);

    // Access and modify the shared variable
    shared_variable++;

    // Signal that the game thread has finished its task
    game_finished = true;
    sem_post(&semaphore); // Increment semaphore to signal completion

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);

    return nullptr;
}
void foodIntersect(){
  for(int i=0;i<59;i++){
    if(food[i].getGlobalBounds().intersects(pac.sp.getGlobalBounds())){
            food[i].setPosition(-100,-100);
            score+=5;
            }
  }
}
void* ghostMovement(void* arg){
    int* value = (int*)arg;
while(1){
 //sem_wait(&ghost[1]);
  /*  if(count==4){
    sem_post(&ga);
    sem_wait(&gh);
    count=0;
   }*/
   pthread_mutex_lock(&mutex);
  std::cout<<count<<std::endl;
   if(*value==1){
     count++;

    if(count==4){
       sem_post(&mg);
       sem_wait(&ga);
       count=0;
     for(int i=0;i<4;i++)
           sem_post(&gh[i]);
      }
       if(permit>0&&key2>0&&gkey[0]==false){
            key2--;
            gkey[0]=true;
           }
        if(gkey[0]==true&&permit>0){
            permit--;
             gpermit[0]=true;
             both[0]=true;
             z++;
        }
                
      if(both[0]==true){
     
    
                
      if(x1==0&&y1<0&&ghostIntersect(ghost[0].sp)){
            ghost[0].sp.setPosition(x5,y5);
            x1=0.1*speed;y1=0*speed;       
      }
      else if(x1>0&&y1==0&&ghostIntersect(ghost[0].sp)){
           ghost[0].sp.setPosition(x5,y5);
           x1=0*speed;y1=0.1*speed;
      }
      else if(x1==0&&y1>0&&ghostIntersect(ghost[0].sp)){
          ghost[0].sp.setPosition(x5,y5);
          y1=0*speed;x1=-0.1*speed;
      }
      else if(y1==0,x1<0&&ghostIntersect(ghost[0].sp)){
            ghost[0].sp.setPosition(x5,y5);
            x1=0*speed;y1=-0.1*speed;
      }
       x5=ghost[0].sp.getPosition().x;
      y5=ghost[0].sp.getPosition().y;
      ghost[0].sp.move(x1,y1);
      if(ghost[0].sp.getGlobalBounds().intersects(gpower[0].getGlobalBounds())){
          gpower[0].setPosition(-100,-100);
          speed=speed*2;
      }

       
      }

      //
        pthread_mutex_unlock(&mutex);
      sem_wait(&gh[0]);     
      
   }
   if(*value==2){
        count++;

    if(count==4){
        sem_post(&mg);
        sem_wait(&ga);
        count=0;
     for(int i=0;i<4;i++)
           sem_post(&gh[i]);
      }
       if(permit>0&&key2>0&&gkey[1]==false){
            key2--;
            gkey[1]=true;
           }
        if(gkey[1]==true&&permit>0){
             permit--;
             gpermit[1]=true;
             both[1]=true;
             z++;
        }
                
      if(both[1]==true){
      if(x2==0&&y2<0&&ghostIntersect(ghost[1].sp)){
            ghost[1].sp.setPosition(x6,y6);
            x2=-0.1;y2=0;       
      }
      else if(x2>0&&y2==0&&ghostIntersect(ghost[1].sp)){
           ghost[1].sp.setPosition(x6,y6);
           x2=0;y2=-0.1;
      }
      else if(x2==0&&y2>0&&ghostIntersect(ghost[1].sp)){
          ghost[1].sp.setPosition(x6,y6);
          y2=0;x2=0.1;
      }
      else if(y2==0,x2<0&&ghostIntersect(ghost[1].sp)){
            ghost[1].sp.setPosition(x6,y6);
            x2=0;y2=0.1;
      }
       x6=ghost[1].sp.getPosition().x;
      y6=ghost[1].sp.getPosition().y;
      ghost[1].sp.move(x2,y2);
      }
       pthread_mutex_unlock(&mutex);
      sem_wait(&gh[1]);    
   }
 
   if(*value==3){
    count++;
    if(count==4){
        sem_post(&mg);
        sem_wait(&ga);
         count=0;
     for(int i=0;i<4;i++)
           sem_post(&gh[i]);
     }   if(permit>0&&key2>0&&gkey[2]==false){
            key2--;
            gkey[2]=true;
           }
        if(gkey[2]==true&&permit>0){
          permit--;
             gpermit[2]=true;
             both[2]=true;
             z++;
        }
                
      if(both[2]==true){
        if(x3==0&&y3<0&&ghostIntersect(ghost[2].sp)){
            ghost[2].sp.setPosition(x7,y7);
            x3=0.1*speed1;y3=0*speed1;       
      }
      else if(x3>0&&y3==0&&ghostIntersect(ghost[2].sp)){
           ghost[2].sp.setPosition(x7,y7);
           x3=0*speed1;y3=0.1*speed1;
      }
      else if(x3==0&&y3>0&&ghostIntersect(ghost[2].sp)){
          ghost[2].sp.setPosition(x7,y7);
          y3=0*speed1;x3=-0.1*speed1;
      }
      else if(y3==0,x3<0&&ghostIntersect(ghost[2].sp)){
            ghost[2].sp.setPosition(x7,y7);
            x3=0*speed1;y3=-0.1*speed1;
      }
       x7=ghost[2].sp.getPosition().x;
      y7=ghost[2].sp.getPosition().y;
      ghost[2].sp.move(x3,y3);
      if(ghost[2].sp.getGlobalBounds().intersects(gpower[0].getGlobalBounds())){
          gpower[2].setPosition(-100,-100);
          speed1=speed1*2;
      }

      
      }
       pthread_mutex_unlock(&mutex);
      sem_wait(&gh[2]); 
  
  }
   if(*value==4){
  count++;
    if(count==4){
        sem_post(&mg);
        sem_wait(&ga);
        count=0;
     for(int i=0;i<4;i++)
           sem_post(&gh[i]);
      }
       if(permit>0&&key2>0&&gkey[3]==false){
            key2--;
            gkey[3]=true;
           }
        if(gkey[3]==true&&permit>0){
            permit--;
             gpermit[3]=true;
             both[3]=true;
             z++;
        }
                
      if(both[3]==true)  {
      if(x4==0&&y4<0&&ghostIntersect(ghost[3].sp)){
            ghost[3].sp.setPosition(x8,y8);
            x4=-0.1;y4=0;       
      }
      else if(x4>0&&y4==0&&ghostIntersect(ghost[3].sp)){
           ghost[3].sp.setPosition(x8,y8);
           x4=0;y4=-0.1;
      }
      else if(x4==0&&y4>0&&ghostIntersect(ghost[3].sp)){
          ghost[3].sp.setPosition(x8,y8);
          y4=0;x4=0.1;
      }
      else if(y4==0,x4<0&&ghostIntersect(ghost[3].sp)){
            ghost[3].sp.setPosition(x8,y8);
            x4=0;y4=0.1;
      }
       x8=ghost[1].sp.getPosition().x;
      y8=ghost[1].sp.getPosition().y;
      ghost[3].sp.move(x4,y4);}
        pthread_mutex_unlock(&mutex);
      sem_wait(&gh[3]); 
   
   
   //sem_post(&gh);
  //sem_wait(&gh);


}
}
}
void* player(void* arg){
       
      while(1){
        x=pac.sp.getPosition().x;
        y=pac.sp.getPosition().y;
         sem_wait(&s);
            std::cout<<"dkflsf"<<std::endl;
     if (key==1) //If left key is pressed
           pac.sp.move(-0.5,0);  // Player will move to left
	else if (key==2) // If right key is pressed
             pac.sp.move(0.5,0);   //player will move to right
else	if (key==3) //If up key is pressed
             pac.sp.move(0,-0.5);   //playet will move upwards
else	if (key==4) // If down key is pressed
             pac.sp.move(0,0.5);

             if(intersect())
                pac.sp.setPosition(x,y); 


      }
     std::cout<<"hello"<<std::endl;
   pthread_exit(NULL);
}

void* game(void* arg) {
    sf::VideoMode mode(800, 600, 32);
    sf::RenderWindow window(mode, "SFML Window", sf::Style::Close);
    
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        foodIntersect();
        // Clear the window
       
        window.clear(sf::Color::Black);
       sem_wait(&mg); 
        palletIntersect();
        if(permit<4){
       manage=cl1.getElapsedTime().asSeconds();
       std::cout<<manage<<std::endl;
       if(manage>10){
        permit++;
        key2++;
        cl1.restart();}
       }
       std::cout<<"hello"<<std::endl;
        // Draw SFML graphics here...
        sf::CircleShape circle(50.f);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(375.f, 275.f);
      //  window.draw(circle);
      //      sem_wait(&ga);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                key=1;
                sem_post(&s); 
            }
     else   if (Keyboard::isKeyPressed(Keyboard::Right)) {
                key=2;
                sem_post(&s); 
            }
            else   if (Keyboard::isKeyPressed(Keyboard::Up)) {
                key=3;
                sem_post(&s); 
            }
              else   if (Keyboard::isKeyPressed(Keyboard::Down)) {
                key=4;
                sem_post(&s); 
            }
            palletIntersect();
            if(check==true){
               for(int i=0;i<4;i++)
               if(pac.sp.getGlobalBounds().intersects(ghost[i].sp.getGlobalBounds())){
                   // permit++;
                  //  key2++;
                    both[i]=0;
                    gkey[i]=0;
                    gpermit[i]=0;
                    ghost[i].sp.setPosition(370,200);
               }
                 tm=cl.getElapsedTime().asSeconds(); 
                 if(tm>15){
                    check=false;
                    tm=0;}

            }
            else{
                   for(int i=0;i<4;i++)
               if(pac.sp.getGlobalBounds().intersects(ghost[i].sp.getGlobalBounds())){
                    pac.sp.setPosition(390,90);
               }
            }   
        window.draw(pac.sp);
        window.draw(obj[0].sp);
        window.draw(obj[2].sp);
        window.draw(obj[3].sp);
        window.draw(obj[1].sp);
        window.draw(obj[4].sp);
        window.draw(obj[5].sp);
        window.draw(obj[6].sp);
        window.draw(obj[7].sp);
        window.draw(obj[8].sp);
        window.draw(obj[9].sp);
        window.draw(obj[10].sp);
        window.draw(obj[11].sp);
        window.draw(obj[12].sp);
         window.draw(obj[13].sp);
         for(int i=0;i<4;i++){
            window.draw(ghost[i].sp);
         }
         for(int i=0;i<59;i++){
             window.draw(food[i]);
         }
         for(int i=0;i<4;i++){
             window.draw(pallets[i]);
         }
         window.draw(gpower[0]);
        //  sem_post(&gh);
        // Display the contents of the window
        window.display();
        sem_post(&ga);
    }
     sem_post(&semaphore); 
     
    return nullptr;
}

int main() {
    pthread_t game_thread;
    // Initialize your object
    obj[0].tex.loadFromFile("wall1.png");
    obj[0].sp.setTexture(obj[0].tex);
    obj[1].tex.loadFromFile("wall2.png");
    obj[1].sp.setTexture(obj[1].tex);
     obj[2].tex.loadFromFile("wall1.png");
    obj[2].sp.setTexture(obj[2].tex);
     obj[3].tex.loadFromFile("wall2.png");
    obj[3].sp.setTexture(obj[3].tex);
     obj[4].tex.loadFromFile("wall1.png");
    obj[4].sp.setTexture(obj[4].tex);
    obj[5].tex.loadFromFile("wall1.png");
    obj[5].sp.setTexture(obj[5].tex);
    obj[6].tex.loadFromFile("wall2.png");
    obj[6].sp.setTexture(obj[6].tex);
    obj[7].tex.loadFromFile("wall2.png");
    obj[7].sp.setTexture(obj[6].tex);
    obj[8].tex.loadFromFile("wall2.png");
    obj[8].sp.setTexture(obj[6].tex);
    obj[9].tex.loadFromFile("wall2.png");
    obj[9].sp.setTexture(obj[6].tex);
 //   obj[10].tex.loadFromFile("wall2.png");
  //  obj[10].sp.setTexture(obj[6].tex);
     obj[11].tex.loadFromFile("wall2.png");
    obj[11].sp.setTexture(obj[6].tex);
    obj[12].tex.loadFromFile("wall1.png");
    obj[12].sp.setTexture(obj[5].tex);
     obj[13].tex.loadFromFile("wall1.png");
    obj[13].sp.setTexture(obj[5].tex);
    
    pac.tex.loadFromFile("pacman.jpeg");
    pac.sp.setTexture(pac.tex);
    ghost[0].tex.loadFromFile("ghost1.png");
    ghost[1].tex.loadFromFile("ghost1.png");
    ghost[2].tex.loadFromFile("ghost1.png");
    ghost[3].tex.loadFromFile("ghost1.png");
    for(int i=0;i<4;i++)
    ghost[i].sp.setTexture(ghost[i].tex);
    pac.sp.setScale(0.1,0.1);
    obj[0].sp.setScale(6,2.5);
    obj[0].sp.setPosition(20,30);
    obj[1].sp.setScale(4,6);
    obj[1].sp.setPosition(20,30);

     obj[2].sp.setScale(6,2.5);
    obj[2].sp.setPosition(750,30);
      obj[3].sp.setScale(4,6);
    obj[3].sp.setPosition(22,505);
     obj[4].sp.setScale(6,1.5);
    obj[4].sp.setPosition(100,150);
    obj[5].sp.setScale(6,1.9);
    obj[5].sp.setPosition(670,100);
    obj[6].sp.setScale(1.3,6);
    obj[6].sp.setPosition(100,100);
    obj[7].sp.setScale(1.3,6);
    obj[7].sp.setPosition(450,100);
    obj[8].sp.setScale(1.3,6);
    obj[8].sp.setPosition(100,430);
    obj[9].sp.setScale(1.3,6);
    obj[9].sp.setPosition(450,430);
    obj[10].sp.setScale(1.2,6);
    obj[10].sp.setPosition(300,200);
    obj[11].sp.setScale(1.2,6);
    obj[11].sp.setPosition(300,330);
      obj[12].sp.setScale(6,0.85);
    obj[12].sp.setPosition(270,200);
     obj[13].sp.setScale(6,0.85);
    obj[13].sp.setPosition(500,200);
    pac.sp.setPosition(390,90);
    for(int i=0;i<4;i++)
    ghost[i].sp.setScale(0.1,0.1);
    ghost[0].sp.setPosition(380,240);
     ghost[1].sp.setPosition(370,240);
     ghost[2].sp.setPosition(400,240);
     ghost[3].sp.setPosition(390,240);
     f.loadFromFile("food.png");
     gp.loadFromFile("gpower.jpeg");
     for(int i=0;i<60;i++){
         food[i].setTexture(f);
         food[i].setScale(0.05,0.05);
     }
     for(int i=0;i<4;i++){
          pallets[i].setTexture(f);
         pallets[i].setScale(0.1,0.1);

     }
      gpower[0].setTexture(gp);
      gpower[1].setTexture(gp);
      gpower[0].scale(0.1,0.1);
      gpower[1].scale(0.1,0.1);
      gpower[0].setPosition(730,440);
      pallets[0].setPosition(55,60);
     for(int v=60,i=0;i<19;i++,v=v+35){
      food[i].setPosition(v,60);
     }
     for(int v=90,i=19;i<30;i++,v=v+35){
           food[i].setPosition(55,v);
     }
     pallets[2].setPosition(55,475);
     
        pallets[1].setPosition(725,60);
        for(int v=90,i=30;i<48;i++,v=v+35){
           food[i].setPosition(v,475);
        }
        pallets[3].setPosition(715,475);
        for(int v=440, i=48;i<59;i++,v=v-35){
                 food[i].setPosition(715,v);
        }
    // Initialize the 
    sem_init(&semaphore, 0, 0);

    // Create the game thread
     int arr[4]={1,2,3,4};
    pthread_create(&game_thread, nullptr, game, &obj);
     pthread_create(&pacman, nullptr, player, &pac);
     for(int i=0;i<4;i++){
      pthread_create(&g[i], nullptr,ghostMovement, (void*)&arr[i]);
      

     }
     
    // Wait for the game thread to finish its task using the semaphore
    sem_wait(&semaphore);
    std::cout<<"hello";
    // Destroy the semaphore
    sem_destroy(&semaphore);

    // Main thread exits here
    return 0;
}
