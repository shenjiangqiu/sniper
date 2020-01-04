#include "simulator.h"
#include "branch_predictor.h"
#include "one_bit_branch_predictor.h"
#include "pentium_m_branch_predictor.h"
#include "config.hpp"
#include "stats.h"
#include "magic_server.h"
#include<string>
BranchPredictor::BranchPredictor()
   : m_correct_predictions(0)
   , m_incorrect_predictions(0)
{
   for(int i=0;i<10;i++){
      correct_branch_predictions_flaged[i]=0;
      incorrect_branch_predictions_flaged[i]=0;
   }
}

BranchPredictor::BranchPredictor(String name, core_id_t core_id)
   : m_correct_predictions(0)
   , m_incorrect_predictions(0)
{
  registerStatsMetric(name, core_id, "num-correct", &m_correct_predictions);
  registerStatsMetric(name, core_id, "num-incorrect", &m_incorrect_predictions);
  
  for (int i = 0; i < 20; i++)
  {
     correct_branch_predictions_flaged[i] = 0;
     incorrect_branch_predictions_flaged[i] = 0;
     registerStatsMetric(name,core_id,(std::string("flagged-num-correct")+std::to_string(i+1)).c_str(),&(correct_branch_predictions_flaged[i]));
     registerStatsMetric(name,core_id,(std::string("flagged-num-incorrect")+std::to_string(i+1)).c_str(),&(incorrect_branch_predictions_flaged[i]));
  }
}

BranchPredictor::~BranchPredictor()
{ 
   std::cout<<"correct predict totoal: "<<m_correct_predictions<<std::endl;
   for(int i=0;i<10;i++){
      std::cout<<"correct flaged "<<i+1<<": "<<correct_branch_predictions_flaged[i]<<std::endl;
   }
   std::cout<<"incorrect predict totoal: "<<m_incorrect_predictions<<std::endl;
   for(int i=0;i<10;i++){
      std::cout<<"correct flaged "<<i+1<<": "<<incorrect_branch_predictions_flaged[i]<<std::endl;
   }
}

UInt64 BranchPredictor::m_mispredict_penalty;

BranchPredictor* BranchPredictor::create(core_id_t core_id)
{
   try
   {
      config::Config *cfg = Sim()->getCfg();
      assert(cfg);

      m_mispredict_penalty = cfg->getIntArray("perf_model/branch_predictor/mispredict_penalty", core_id);

      String type = cfg->getStringArray("perf_model/branch_predictor/type", core_id);
      if (type == "none")
      {
         return 0;
      }
      else if (type == "one_bit")
      {
         UInt32 size = cfg->getIntArray("perf_model/branch_predictor/size", core_id);
         return new OneBitBranchPredictor("branch_predictor", core_id, size);
      }
      else if (type == "pentium_m")
      {
         return new PentiumMBranchPredictor("branch_predictor", core_id);
      }
      else
      {
         LOG_PRINT_ERROR("Invalid branch predictor type.");
         return 0;
      }
   }
   catch (...)
   {
      LOG_PRINT_ERROR("Config info not available while constructing branch predictor.");
      return 0;
   }
}

UInt64 BranchPredictor::getMispredictPenalty()
{
   return m_mispredict_penalty;
}

void BranchPredictor::resetCounters()
{
  m_correct_predictions = 0;
  m_incorrect_predictions = 0;
}

void BranchPredictor::updateCounters(bool predicted, bool actual)
{
   if (predicted == actual)
   {

      ++m_correct_predictions;
      if (Sim()->getMagicServer()->isSetBranchFlag())
      {
         assert(Sim()->getMagicServer()->inWhichBranchFlag()-1<20);
         correct_branch_predictions_flaged[Sim()->getMagicServer()->inWhichBranchFlag()-1]++;
      }
   }
   else
   {
      ++m_incorrect_predictions;
      if (Sim()->getMagicServer()->isSetBranchFlag())
      {
         assert(Sim()->getMagicServer()->inWhichBranchFlag()-1<20);

         incorrect_branch_predictions_flaged[Sim()->getMagicServer()->inWhichBranchFlag()-1]++;
      }
   }
}
