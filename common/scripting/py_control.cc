#include "hooks_py.h"
#include "simulator.h"
#include "magic_server.h"
#include "sim_api.h"

static PyObject *
setROI(PyObject *self, PyObject *args)
{
   bool inRoi = false;

   if (!PyArg_ParseTuple(args, "b", &inRoi))
      return NULL;

   Sim()->getMagicServer()->setPerformance(inRoi);

   Py_RETURN_NONE;
}

static PyObject*
setBranchFlag(PyObject *self,PyObject *args){
   int typeNumber;
   if (!PyArg_ParseTuple(args, "b", &typeNumber))//type 1, type2 ....
      return NULL;
   Sim()->getMagicServer()->BranchFlag(true,typeNumber);

   Py_RETURN_NONE;
}
static PyObject*
unsetBranchFlag(PyObject *self,PyObject *args){
   
   Sim()->getMagicServer()->BranchFlag(false,0);

   Py_RETURN_NONE;
}

static PyObject*
setFixMemoryAdrees(PyObject *self,PyObject *args){
   int typeNumber;
   if (!PyArg_ParseTuple(args, "b", &typeNumber))//type 1, type2 ....
      return NULL;
   Sim()->getMagicServer()->setFixAdress(true,typeNumber);

   Py_RETURN_NONE;
}
static PyObject*
unsetFixMemoryAdrees(PyObject *self,PyObject *args){
   
   Sim()->getMagicServer()->setFixAdress(false);

   Py_RETURN_NONE;
}
static PyObject *
setInstrumentationMode(PyObject *self, PyObject *args)
{
   long int mode = 999;

   if (!PyArg_ParseTuple(args, "l", &mode))
      return NULL;

   switch (mode)
   {
      case SIM_OPT_INSTRUMENT_DETAILED:
      case SIM_OPT_INSTRUMENT_WARMUP:
      case SIM_OPT_INSTRUMENT_FASTFORWARD:
         Sim()->getMagicServer()->Magic_unlocked(INVALID_CORE_ID, INVALID_THREAD_ID, SIM_CMD_INSTRUMENT_MODE, mode, 0);
         break;
      default:
         LOG_PRINT_ERROR("Unexpected instrumentation mode from python: %lx.", mode);
         return NULL;
   }

   Py_RETURN_NONE;
}

static PyObject *
setProgress(PyObject *self, PyObject *args)
{
   float progress = 0;

   if (!PyArg_ParseTuple(args, "f", &progress))
      return NULL;

   Sim()->getMagicServer()->setProgress(progress);

   Py_RETURN_NONE;
}

static PyObject *
simulatorAbort(PyObject *self, PyObject *args)
{
   // Exit now, cleaning up as best as possible
   // For benchmarks where, after ROI, functionally simulating until the end takes too long.

   // If we're still in ROI, make sure we end it properly
   Sim()->getMagicServer()->setPerformance(false);

   LOG_PRINT("Application exit.");
   Simulator::release();

   exit(0);
}

static PyMethodDef PyControlMethods[] = {
   { "set_roi", setROI, METH_VARARGS, "Set whether or not we are in the ROI" },
   {"set_fix_memory_adrees",setFixMemoryAdrees,METH_VARARGS,"Start to access fixed memory address"},
   {"unset_fix_memory_adrees",unsetFixMemoryAdrees,METH_VARARGS,"end to access fixed memory address"},
   {"setBranchFlag",setBranchFlag,METH_VARARGS,"Start to set branch flag"},
   {"unsetBranchFlag",unsetBranchFlag,METH_VARARGS,"end to set branch flag"},
   { "set_instrumentation_mode", setInstrumentationMode, METH_VARARGS, "Set instrumentation mode" },
   { "set_progress", setProgress, METH_VARARGS, "Set simulation progress indicator (0..1)" },
   { "abort", simulatorAbort, METH_VARARGS, "Stop simulation now" },
   { NULL, NULL, 0, NULL } /* Sentinel */
};

void HooksPy::PyControl::setup(void)
{
   PyObject *pModule = Py_InitModule("sim_control", PyControlMethods);

   {
      PyObject *pGlobalConst = PyInt_FromLong(SIM_OPT_INSTRUMENT_DETAILED);
      PyObject_SetAttrString(pModule, "DETAILED", pGlobalConst);
      Py_DECREF(pGlobalConst);
   }
   {
      PyObject *pGlobalConst = PyInt_FromLong(SIM_OPT_INSTRUMENT_WARMUP);
      PyObject_SetAttrString(pModule, "WARMUP", pGlobalConst);
      Py_DECREF(pGlobalConst);
   }
   {
      PyObject *pGlobalConst = PyInt_FromLong(SIM_OPT_INSTRUMENT_FASTFORWARD);
      PyObject_SetAttrString(pModule, "FASTFORWARD", pGlobalConst);
      Py_DECREF(pGlobalConst);
   }
}
