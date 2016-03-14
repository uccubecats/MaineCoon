#include <fl/Headers.h>

class JetStream {
  private: 
    // FL Lite overall engine
    fl::Engine* m_engine;

    // Input doubles
    fl::InputVariable* m_altitude;
    fl::InputVariable* m_temp;
    fl::InputVariable* m_pressure;

    // Output double for jet stream
    fl::OutputVariable* m_jetStream;

    // Rule class
    fl::RuleBlock* m_rules;

  public:
	JetStream();
    double probablilityInJetStream(double altitude, double temperature, double pressure);
	~JetStream();

};

extern "C" {
    JetStream* JetStream_new(){
        return new JetStream();
    }
    int JetStream_probablilityInJetStream(JetStream* jsPtr, int a, int t, int p){
        return int(jsPtr->probablilityInJetStream(1.0*a, 1.0*t, 1.0*p));
    }
}
