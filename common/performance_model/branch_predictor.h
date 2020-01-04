#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <iostream>

#include "fixed_types.h"

class BranchPredictor
{
public:
   BranchPredictor();
   BranchPredictor(String name, core_id_t core_id);
   virtual ~BranchPredictor();

   virtual bool predict(IntPtr ip, IntPtr target) = 0;
   virtual void update(bool predicted, bool actual, IntPtr ip, IntPtr target) = 0;

   UInt64 getMispredictPenalty();
   static BranchPredictor* create(core_id_t core_id);

   UInt64 getNumCorrectPredictions() { return m_correct_predictions; }
   UInt64 getNumIncorrectPredictions() { return m_incorrect_predictions; }

   void resetCounters();

protected:
   void updateCounters(bool predicted, bool actual);

private:
   UInt64 m_correct_predictions;
   UInt64 m_incorrect_predictions;
   UInt64 correct_branch_predictions_flaged[20];
   UInt64 incorrect_branch_predictions_flaged[20];

   static UInt64 m_mispredict_penalty;
};

#endif
