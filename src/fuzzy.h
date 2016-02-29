#include "libs/Headers.h"

class JetStream {
  private: 
    // FL Lite overall engine
    Engine* m_engine;

    // Input doubles
    InputVariable* m_altitude;
    InputVariable* m_temp;
    InputVariable* m_pressure;

    // Output double for jet stream
    OutputVariable* m_jetStream;

    // Rule class
    RuleBlock* m_rules;

  public:
    double probablilityInJetStream(double altitude, double temperature, double pressure);
}