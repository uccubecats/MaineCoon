#include "fuzzy.h"

JetStream::JetStream(){
  // Sets up the fuzzy logic unit to be used for calculating probability

  m_engine -> setName("jetstream-probability");

  // Altitude variable
  m_altitude -> setName("Altitude");
  m_altitude -> setRange(-5.000, 40.000);

  // m_altitude membership functions (left, right)
  m_altitude -> addTerm(new Triangle("JETSTREAM", 7.000, 12.000));
  m_altitude -> addTerm(new Triangle("MAXHEIGHT", 20.000, 40.000));
  m_altitude -> addTerm(new Triangle("MINHEIGHT", -5.000, 5.000));


  // Temperature variable
  m_temp -> setName("Temperature");
  m_temp -> setRange(-80.000, 50.000);

  // m_temperature membership functions (left, right)
  m_temp -> addTerm(new Triangle("VERYCOLD", -80.000, -40.000));
  m_temp -> addTerm(new Triangle("NORMAL", -10.000, 50.000));
  m_temp -> addTerm(new Triangle("COLD", -40.000, 0.000));


  // Pressure variable
  m_pressure -> setName("Pressure");
  m_pressure -> setRange(-50000.000, 150000.000);

  // m_pressure membership functions (left, right)
  m_pressure -> addTerm(new Triangle("LOW", -50000.000, 50000.000));
  m_pressure -> addTerm(new Triangle("MEDIUM", 0.000, 100000.000));
  m_pressure -> addTerm(new Triangle("HIGH", 50000.000, 150000.000));


  // Jet stream probability variable
  m_jetStream -> setName("JetStream");
  m_jetStream -> setRange(0.000, 100.000);

  // Jet stream membership functions (left, right)
  m_jetStream -> addTerm(new Triangle("YES", 50.000, 150.000));
  m_jetStream -> addTerm(new Triangle("MAYBE", 30.000, 70.000));
  m_jetStream -> addTerm(new Triangle("NO", -50.000, 50.000));

  // Let engine know about the input and output variables
  m_engine -> addInputVariable(m_altitude);
  m_engine -> addInputVariable(m_temp);
  m_engine -> addInputVariable(m_pressure);
  m_engine -> addOutputVariable(m_jetStream);


  // Add rules to RuleBlock, parsed using the m_engine
  m_rules -> addRule(Rule::parse("if Altitude is JETSTREAM then jetStream is YES", m_engine));
  m_rules -> addRule(Rule::parse("if Temperature is VERYCOLD and 
                                (Pressure is LOW or Pressure is MEDIUM)
                                then jetStream is YES", m_engine));
  m_rules -> addRule(Rule::parse("if Temperature is COLD then jetStream is MAYBE", m_engine));
  m_rules -> addRule(Rule::parse("if Pressure is LOW or Pressure is MEDIUM 
                                then jetStream is MAYBE", m_engine));
  m_rules -> addRule(Rule::parse("if Pressure is HIGH or Temperature is NORMAL
                                then jetStream is NO", m_engine));
  m_rules -> addRule(Rule::parse("if Altitude is MAXHEIGHT or Altitude is MINHEIGHT
                                then jetStream is YES", m_engine));
}

JetStream::~JetStream(){
  // Basic deconstructor. Check for, delete.
  if (m_engine){
    delete[] m_engine;
  }
  if (m_altitude){
    delete[] m_altitude;
  }
  if (m_temp){
    delete[] m_temp;
  }
  if (m_pressure){
    delete[] m_pressure;
  }
  if (m_jetStream){
    delete[] m_jetStream;
  }
  if (m_rules){
    delete[] m_rules;
  }

}

double probablilityInJetStream(double altitude, double temperature, double pressure){
  // Set all input variables to respective arguments
  m_altitude -> setInputValue(altitude);
  m_temp -> setInputValue(temperature);
  m_pressure -> setInputValue(pressure);

  // Process the input variables, results in a probability
  m_engine -> process();

  return jetStream->getOutputValue();
}