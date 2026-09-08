// Robot 2 roues motorisées (Arduino Motor Shield Rev3) + capteur photoélectrique TOR
#define DIRD 12
#define PWMD 3
#define DIRG 13
#define PWMG 11
#define CAPTEUR 2   // capteur TOR : LOW = ligne détectée (à adapter si logique inverse)

const int pwm_roues = 120;
const unsigned long tps_ligne = 2000; // durée (ms) pendant laquelle les 2 roues avancent

void setup() {
  pinMode(DIRD, OUTPUT);
  pinMode(DIRG, OUTPUT);
  pinMode(CAPTEUR, INPUT_PULLUP);
  digitalWrite(DIRD, HIGH);
  digitalWrite(DIRG, HIGH);
}

void loop() {
  static bool termine = false;
  if (termine) return;                            // la séquence ne s'exécute qu'une fois

  delay(3000);                                   // 1. attendre 3s

  analogWrite(PWMD, pwm_roues);                   // 2. tourner la roue droite jusqu'à détection
  while (digitalRead(CAPTEUR) == HIGH);

  analogWrite(PWMG, pwm_roues);                   // 3. les deux roues à la même vitesse pendant tps_ligne
  delay(tps_ligne);

  analogWrite(PWMD, 0);
  analogWrite(PWMG, 0);
  termine = true;
}
