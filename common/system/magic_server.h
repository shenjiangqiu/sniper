#ifndef MAGIC_SERVER_H
#define MAGIC_SERVER_H

#include "fixed_types.h"
#include "progress.h"

class MagicServer
{
   public:
      // data type to hold arguments in a HOOK_MAGIC_MARKER callback
      struct MagicMarkerType {
         thread_id_t thread_id;
         core_id_t core_id;
         UInt64 arg0, arg1;
         const char* str;
      };

      MagicServer();
      ~MagicServer();

      UInt64 Magic(thread_id_t thread_id, core_id_t core_id, UInt64 cmd, UInt64 arg0, UInt64 arg1);
      bool inROI(void) const { return m_performance_enabled; }
      static UInt64 getGlobalInstructionCount(void);

      // To be called while holding the thread manager lock
      UInt64 Magic_unlocked(thread_id_t thread_id, core_id_t core_id, UInt64 cmd, UInt64 arg0, UInt64 arg1);
      UInt64 setFrequency(UInt64 core_number, UInt64 freq_in_mhz);
      UInt64 getFrequency(UInt64 core_number);

      void enablePerformance();
      void restartPerformance();
      void pausePerformance();
      void disablePerformance();
      UInt64 setPerformance(bool enabled);

      UInt64 setInstrumentationMode(UInt64 sim_api_opt);

      void setProgress(float progress) { m_progress.setProgress(progress); }
      void setFixAdress(bool set,unsigned char fix_address=-1){
         //printf("set  %d %d\n",set,fix_address);
         is_fix_address=set;
         fix_address_number=fix_address;
      }
      bool isInFixedAdress(){
         return is_fix_address;
      }
      unsigned char inWhichFixAddress(){
         return fix_address_number;
      }
      void BranchFlag(bool f,int n){//n is from 1 ~ 20
         //std::cout<<"set branch:"<<f<<", "<<n<<std::endl;
         is_branch_flag=f;
         branch_number=n;
      }
      bool isSetBranchFlag(){
         return is_branch_flag;
      }
      unsigned char inWhichBranchFlag(){
         return branch_number;
      }
      
   private:
      bool m_performance_enabled;
      Progress m_progress;
      bool is_fix_address=false;
      unsigned char fix_address_number;
      bool is_branch_flag=false;
      unsigned char branch_number;

};

#endif // SYNC_SERVER_H
