#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;
std_msgs::Float64 Distance;
ros::Publisher chatter("chatter",&Distance);       //Do un nome al mio nodo ROS per l'ultrasuoni, parametrico con &Distance

// definisco i numeri dei pin digitali relativi ai due impulsi
const int trigPin = 9;
const int echoPin = 10;

// definizione variabili    NB: ho utilizzato il float in quanto con int i valori alti non sono supportati
long durata;
float distanza;

void setup() {
nh.initNode();            //inizializzo il nodo ROS
nh.advertise(chatter);    
pinMode(trigPin, OUTPUT); // Setto il trig come Outrput
pinMode(echoPin, INPUT); // Setto l'echo come Input
Serial.begin(57600); // Inizio comunicazione seriale
}

void loop() {
// Libero il trig per l'operazione successiva
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Infatti setto lo stato del trig ogni 10 microsecondi (spento,acceso,spento) per inviare un suono che verrà captato dall'echo
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Lettura dell'echo e ritorno della durata del suono in microsecondi
durata = pulseIn(echoPin, HIGH);

// Calcolo la distanza
distanza= durata*0.034/2;         //velocità del suono (0.034) a circa 20° moltiplicato per la durata, /2 sennò si considera andata e ritorno

//pub data

Distance.data = distanza;
chatter.publish(&Distance);
nh.spinOnce();
//Per stampare la distanza sul monitor in cm:  NB non serve in quanto con rostopic echo /chatter posso vederla con ROS
//Serial.print("Distanza: ");
//Serial.println(distanza);
delay(100);
}
