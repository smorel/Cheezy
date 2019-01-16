
#define UNUSABLE \
cPreProcessor::unusable*

#define IS_VOID(T) \
cPreProcessor::is_void<T>::value

#define IS_USABLE(T) \
cPreProcessor::is_usable<T>::value

#define CLASS_SWITCH(condition, A, B) \
cPreProcessor::select_switch<condition, A, B>::value

struct cPreProcessor
{
    struct unusable
    {
    };

    template <typename T>
    struct is_void
    { enum { value = false }; };

    template <>
    struct is_void<void>
    { enum { value = true }; };

    template <typename T>
    struct is_usable
    { enum { value = 1 }; };

    template <>
    struct is_usable<unusable*>
    { enum { value = 0 }; };

    template<int condition, class A, class B>
    struct select_switch
    {
        typedef typename UNUSABLE value;
    };

    template<class A, class B>
    struct select_switch<true, A, B>
    {
        typedef typename A value;
    };

    template<class A, class B>
    struct select_switch<false, A, B>
    {
        typedef typename B value;
    };
};


template <class tRet, class tArg1=UNUSABLE,
                      class tArg2=UNUSABLE,
                      class tArg3=UNUSABLE,
                      class tArg4=UNUSABLE,
                      class tArg5=UNUSABLE>
class cCallBase
{
public:
    // if callback function returns void: set return type to unusable
    typedef typename CLASS_SWITCH(IS_VOID(tRet), UNUSABLE, tRet)  ret_type;

    // the callbacks to static functions
    typedef ret_type (*tFunctionS0)();
    typedef ret_type (*tFunctionS1)(tArg1);
    typedef ret_type (*tFunctionS2)(tArg1, tArg2);
    typedef ret_type (*tFunctionS3)(tArg1, tArg2, tArg3);
    typedef ret_type (*tFunctionS4)(tArg1, tArg2, tArg3, tArg4);
    typedef ret_type (*tFunctionS5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // storage of callback to static functions
    struct kDataS
    {
        int s32_Params; // number of valid arguments
        union
        {
            tFunctionS0  S0;
            tFunctionS1  S1;
            tFunctionS2  S2;
            tFunctionS3  S3;
            tFunctionS4  S4;
            tFunctionS5  S5;
        } f_Func;
    };

    // the callbacks to member functions of a C++ class
    typedef ret_type (cCallBase::*tFunctionM0)();
    typedef ret_type (cCallBase::*tFunctionM1)(tArg1);
    typedef ret_type (cCallBase::*tFunctionM2)(tArg1, tArg2);
    typedef ret_type (cCallBase::*tFunctionM3)(tArg1, tArg2, tArg3);
    typedef ret_type (cCallBase::*tFunctionM4)(tArg1, tArg2, tArg3, tArg4);
    typedef ret_type (cCallBase::*tFunctionM5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // storage of callback to class member functions
    struct kDataM
    {
        int       s32_Params; // number of valid arguments
        cCallBase *pi_Inst;
        union
        {
            tFunctionM0  M0;
            tFunctionM1  M1;
            tFunctionM2  M2;
            tFunctionM3  M3;
            tFunctionM4  M4;
            tFunctionM5  M5;
        } f_Func;
    };

    ret_type Execute()
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1)
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2)
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3)
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4)
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4, tArg5 Arg5)
    {
        assert(0); // this is never executed (function is overridden)
        return ret_type();
    }

protected:
    kDataS k_DataS;
    kDataM k_DataM;
};

template <class tRet, class tArg1=UNUSABLE,
                      class tArg2=UNUSABLE,
                      class tArg3=UNUSABLE,
                      class tArg4=UNUSABLE,
                      class tArg5=UNUSABLE>

class cCall : public virtual cCallBase<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>
{
public:
    // the callbacks to functions in a virtually derived class
    typedef ret_type (cCall::*tFunctionV0)();
    typedef ret_type (cCall::*tFunctionV1)(tArg1);
    typedef ret_type (cCall::*tFunctionV2)(tArg1, tArg2);
    typedef ret_type (cCall::*tFunctionV3)(tArg1, tArg2, tArg3);
    typedef ret_type (cCall::*tFunctionV4)(tArg1, tArg2, tArg3, tArg4);
    typedef ret_type (cCall::*tFunctionV5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // storage of virtual callback
    struct kDataV
    {
        int   s32_Params; // number of valid arguments
        cCall *pi_Inst;
        union
        {
            tFunctionV0  V0;
            tFunctionV1  V1;
            tFunctionV2  V2;
            tFunctionV3  V3;
            tFunctionV4  V4;
            tFunctionV5  V5;
        } f_Func;
    };

    cCall()
    {
        memset(&k_DataM, 0, sizeof(k_DataM));
        memset(&k_DataV, 0, sizeof(k_DataV));
        memset(&k_DataS, 0, sizeof(k_DataS));
    }

    // Set external Callback or clear Callback
    cCall& operator=(cCall<tRet, tArg1, tArg2, tArg3, tArg4, tArg5> &i_Callback)
    {
        if (&i_Callback)
        {
            k_DataV = i_Callback.k_DataV;
            k_DataM = i_Callback.k_DataM;
            k_DataS = i_Callback.k_DataS;
        }
        else cCall();
        return *this;
    }

    bool Valid()
    {
        return (k_DataM.f_Func.M0 && k_DataM.pi_Inst) || 
               (k_DataV.f_Func.V0 && k_DataV.pi_Inst) ||
                k_DataS.f_Func.S0;
    }

    ret_type Execute()
    {
        if (Check('S', 0)) return                   (k_DataS.f_Func.S0)();
        if (Check('M', 0)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M0)();
        if (Check('V', 0)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V0)();

        assert(0); // callback is uninitialized or too few arguments passed to Execute() !
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1)
    {
        if (Check('S', 1)) return                   (k_DataS.f_Func.S1)(Arg1);
        if (Check('M', 1)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M1)(Arg1);
        if (Check('V', 1)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V1)(Arg1);

        assert(0); // callback is uninitialized or too few arguments passed to Execute() !
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2)
    {
        if (Check('S', 2)) return                   (k_DataS.f_Func.S2)(Arg1, Arg2);
        if (Check('M', 2)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M2)(Arg1, Arg2);
        if (Check('V', 2)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V2)(Arg1, Arg2);

        assert(0); // callback is uninitialized or too few arguments passed to Execute() !
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3)
    {
        if (Check('S', 3)) return                   (k_DataS.f_Func.S3)(Arg1, Arg2, Arg3);
        if (Check('M', 3)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M3)(Arg1, Arg2, Arg3);
        if (Check('V', 3)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V3)(Arg1, Arg2, Arg3);

        assert(0); // callback is uninitialized or too few arguments passed to Execute() !
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4)
    {
        if (Check('S', 4)) return                   (k_DataS.f_Func.S4)(Arg1, Arg2, Arg3, Arg4);
        if (Check('M', 4)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M4)(Arg1, Arg2, Arg3, Arg4);
        if (Check('V', 4)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V4)(Arg1, Arg2, Arg3, Arg4);

        assert(0); // callback is uninitialized or too few arguments passed to Execute() !
        return ret_type();
    }

    ret_type Execute(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4, tArg5 Arg5)
    {
        if (Check('S', 5)) return                   (k_DataS.f_Func.S5)(Arg1, Arg2, Arg3, Arg4, Arg5);
        if (Check('M', 5)) return (k_DataM.pi_Inst->*k_DataM.f_Func.M5)(Arg1, Arg2, Arg3, Arg4, Arg5);
        if (Check('V', 5)) return (k_DataV.pi_Inst->*k_DataV.f_Func.V5)(Arg1, Arg2, Arg3, Arg4, Arg5);

        assert(0); // callback is uninitialized!
        return ret_type();
    }

protected:
    kDataV k_DataV;

    bool Check(char s8_Type, int s32_ParamCount)
    {
        switch (s8_Type)
        {
        case 'S': // static
            return (k_DataS.f_Func.S0 && k_DataS.s32_Params == s32_ParamCount);
        case 'M': // member
            return (k_DataM.f_Func.M0 && k_DataM.s32_Params == s32_ParamCount && k_DataM.pi_Inst);
        case 'V': // virtual
            return (k_DataV.f_Func.V0 && k_DataV.s32_Params == s32_ParamCount && k_DataV.pi_Inst);
        default:
            return false;
        }
    }
};

// use this for callbacks to C++ member functions
template <class cInstance, class tRet, class tArg1=UNUSABLE,
                                       class tArg2=UNUSABLE,
                                       class tArg3=UNUSABLE,
                                       class tArg4=UNUSABLE,
                                       class tArg5=UNUSABLE>
class cCallGen : public cCall<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>
{
public:
    typedef tRet (cInstance::*tFunction0)();
    typedef tRet (cInstance::*tFunction1)(tArg1);
    typedef tRet (cInstance::*tFunction2)(tArg1, tArg2);
    typedef tRet (cInstance::*tFunction3)(tArg1, tArg2, tArg3);
    typedef tRet (cInstance::*tFunction4)(tArg1, tArg2, tArg3, tArg4);
    typedef tRet (cInstance::*tFunction5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // Chose the correct argument count
    typedef typename CLASS_SWITCH(IS_USABLE(tArg5), tFunction5, tFunction4)  tFunctionA;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg4), tFunctionA, tFunction3)  tFunctionB;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg3), tFunctionB, tFunction2)  tFunctionC;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg2), tFunctionC, tFunction1)  tFunctionM;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg1), tFunctionM, tFunction0)  tFunction;

    struct kRetFunc
    {
        int     s32_Params; // number of valid arguments
        void    *pi_Inst;
        tFunction f_Func;
    };

    // Constructor
    cCallGen (cInstance *pi_Instance, tFunction f_Func)
    {
        int s32_Params = IS_USABLE(tArg1) + IS_USABLE(tArg2) + IS_USABLE(tArg3) + IS_USABLE(tArg4) + IS_USABLE(tArg5);

        kRetFunc k_RetFunc = { s32_Params, pi_Instance, f_Func };

        if (sizeof(k_RetFunc) == sizeof(k_DataV))
        {
            // sizeof(f_Func) = 12
            memcpy(&k_DataV, &k_RetFunc, sizeof(k_DataV));
        }
        else if (sizeof(k_RetFunc) == sizeof(k_DataM))
        {
            // sizeof(f_Func) = 4
            memcpy(&k_DataM, &k_RetFunc, sizeof(k_DataM));
        }
        else
        {
            assert(0); // Unknown compiler error
        }
    }
};

// use this for callbacks to static C++ functions
template <class tRet, class tArg1=UNUSABLE,
                      class tArg2=UNUSABLE,
                      class tArg3=UNUSABLE,
                      class tArg4=UNUSABLE,
                      class tArg5=UNUSABLE>
class cCallGenS : public cCall<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>
{
public:
    typedef tRet (*tFunction0)();
    typedef tRet (*tFunction1)(tArg1);
    typedef tRet (*tFunction2)(tArg1, tArg2);
    typedef tRet (*tFunction3)(tArg1, tArg2, tArg3);
    typedef tRet (*tFunction4)(tArg1, tArg2, tArg3, tArg4);
    typedef tRet (*tFunction5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // Chose the correct argument count
    typedef typename CLASS_SWITCH(IS_USABLE(tArg5), tFunction5, tFunction4)  tFunctionA;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg4), tFunctionA, tFunction3)  tFunctionB;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg3), tFunctionB, tFunction2)  tFunctionC;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg2), tFunctionC, tFunction1)  tFunctionM;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg1), tFunctionM, tFunction0)  tFunction;

    struct kRetFunc
    {
        int     s32_Params; // number of valid arguments
        tFunction f_Func;
    };

    // Constructor
    cCallGenS (tFunction f_Func)
    {
        int s32_Params = IS_USABLE(tArg1) + IS_USABLE(tArg2) + IS_USABLE(tArg3) + IS_USABLE(tArg4) + IS_USABLE(tArg5);

        kRetFunc k_RetFunc = { s32_Params, f_Func };

        // sizeof(f_Func) = 4
        memcpy(&k_DataS, &k_RetFunc, sizeof(k_DataS));
    }
};

// abstract base class for both: signals and slots

template <class tRet, class tArg1=UNUSABLE,
                      class tArg2=UNUSABLE,
                      class tArg3=UNUSABLE,
                      class tArg4=UNUSABLE,
                      class tArg5=UNUSABLE>
class cSigSlotBase
{
protected:
    // --- base definitions

    typedef typename CLASS_SWITCH(IS_VOID(tRet), UNUSABLE, tRet)  ret_type;

    typedef cSigSlotBase<tRet, tArg1, tArg2, tArg3, tArg4, tArg5> tBase;

    typedef typename std::vector<tBase*>           tList;
    typedef typename std::vector<tBase*>::iterator tIter;

    enum eType { E_Slot, E_Signal };

    // --- base members

    tList          mi_List;           // list of connected slots / signals
    eType          me_Type;           // either E_Slot or E_Signal
    char           *mps8_MyName;      // user defined name only for debugging

    unsigned int mu32_MinInterval;    // minimum interval between two fire events
    ret_type       mr_DefaultInterval;// value to return if signal does not fire
    double         md_LastFire;       // time in ms since 1970 of last fire request

    bool           mb_Reentrance;     // catch reentrant calls
    ret_type       mr_DefaultReenter; // return value if signal/slot is called reentrant

    // --- base functions

    // find a signal or slot in the connected list
    bool Find(tBase &i_Base, tIter &i_Pos)
    {
        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (*i == &i_Base)
            {
                i_Pos = i;
                return true;
            }
        }
        return false;
    }

    // remove a signal or slot from the connected list
    void Remove(tBase &i_Base)
    {
        tIter i;
        if (Find(i_Base, i)) mi_List.erase(i);
    }

    // insert a new signal or slot at the beginning or end of the connected list
    void Insert(tBase &i_Base, bool b_Append=true)
    {
        tIter i;
        if (!Find(i_Base, i))  // check if connection already exists
        {
            mi_List.insert(b_Append ? mi_List.end() : mi_List.begin(), &i_Base);
        }
    }

    // return false if the elapsed time between 2 fire requests is < mu32_MinInterval
    bool CheckInterval()
    {
        if (!mu32_MinInterval)
            return true;

        struct _timeb k_Now;
        _ftime (&k_Now);

        // calc current time since 1970 in milliseconds
        double d_Now = ((double) k_Now.time) * 1000 + k_Now.millitm;

        bool b_Ret = (md_LastFire + mu32_MinInterval <= d_Now);

        md_LastFire = d_Now;
        return b_Ret;
    }

    // will be overwritten only by a slot
    virtual bool Valid()
    {
        return true;
    }

public:
    virtual ret_type Fire() =0;
    virtual ret_type Fire(tArg1 Arg1) =0;
    virtual ret_type Fire(tArg1 Arg1, tArg2 Arg2) =0;
    virtual ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3) =0;
    virtual ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4) =0;
    virtual ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4, tArg5 Arg5) =0;

    // connect a signal with a slot or a slot with a signal
    void Connect(tBase &i_Base, bool b_Append=true)
    {
        // you cannot connect a slot or a signal to itself !
        if (&i_Base == this)
            { assert(0); return; }

        // you cannot connect a slot to a slot or a signal to a signal
        if (me_Type == i_Base.me_Type)
            { assert(0); return; }

        // You have to call AssignFunction() on the slot before connecting it
        if (!i_Base.Valid() || !Valid())
            { assert(0); return; }

        i_Base.Insert(*this, b_Append);
        Insert(i_Base, b_Append);
    }

    // disconnect a signal from this slot or a slot from this signal
    void Disconnect(tBase &i_Base)
    {
        i_Base.Remove(this);
        Remove(i_Base);
    }

    void DisconnectAll()
    {
        for (unsigned int i=0; i<mi_List.size(); i++)
        {
            mi_List.at(i)->Remove(*this);
        }
        mi_List.clear();
    }

    // set the timeout to ignore series of Fire() events
    // and the default return value to return if the fire event is blocked
    void SetMinInterval(unsigned int u32_Milliseconds, ret_type r_ReturnValue)
    {
        mu32_MinInterval   = u32_Milliseconds;
        mr_DefaultInterval = r_ReturnValue;
    }

    // get the number of slots connected to this signal
    // or the number of signals connected to this slot
    int GetConnectedCount()
    {
        return mi_List.size();
    }

    // for debugging purposes
    // lists all slots / signals connected to this signal / slot
    // return false if buffer too small
    // For higher speed I don't use string here
    bool GetConnectedList(char *ps8_Buf, int s32_BufLen)
    {
        if (s32_BufLen < (int)strlen(mps8_MyName) +50)
            return false;

        sprintf(ps8_Buf, "%s %s is connected to: ", (me_Type==E_Slot?"Slot":"Signal"), mps8_MyName);

        if (!mi_List.size()) strcat(ps8_Buf, "Nothing\n");
        else
        {
            s32_BufLen -= strlen(ps8_Buf);

            for (unsigned int i=0; i<mi_List.size(); i++)
            {
                char *ps8_Name = mi_List.at(i)->mps8_MyName;

                s32_BufLen -= (strlen(ps8_Name) +2);
                if (s32_BufLen <= 5)
                    return false;

                if (i) strcat(ps8_Buf, ", ");
                strcat(ps8_Buf, ps8_Name);
            }
        }
        return true;
    }

    // constructor (signal + slot)
    cSigSlotBase()
    {
        md_LastFire        = 0;
        mu32_MinInterval   = 0;
    }

    // destructor (disonnects all connected signals / slots)
    ~cSigSlotBase()
    {
        DisconnectAll();
    }
};

// for callbacks to Member functions
#define MAKE_COMBINE_M(Class, Instance, Function, RetType) cCallGen<Class, bool, RetType*, RetType>(Instance, Function)
// for callbacks to Static functions
#define MAKE_COMBINE_S(                 Function, RetType) cCallGenS<      bool, RetType*, RetType>(          Function)


template <class tRet, class tArg1=UNUSABLE,
                      class tArg2=UNUSABLE,
                      class tArg3=UNUSABLE,
                      class tArg4=UNUSABLE,
                      class tArg5=UNUSABLE>
class cSignal : public cSigSlotBase<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>
{
protected:

    ret_type    mr_DefaultCombine;               // return value if no slot connected
    cCall<bool, ret_type*, ret_type> mi_Combine; // function to combine the slots return values

    // this function does nothing, it will be replaced when
    // SetCombineFunction() is called and a "real" combine function was set
    bool CombineDummy(ret_type *p_Result, ret_type r_NewValue)
    {
        *p_Result = r_NewValue;
        return true; // true = continue calling the next slot in the connected list
    }

public:
    // constructor
    cSignal(ret_type r_DefaultReenter = (ret_type) 0,
            char     *ps8_Name        = "NoName-Signal")
    {
        mps8_MyName       = ps8_Name;
        me_Type           = E_Signal;
        mr_DefaultReenter = r_DefaultReenter;
        mb_Reentrance     = false;
        mi_Combine        = MAKE_COMBINE_M(cSignal, this, &cSignal::CombineDummy, ret_type);
    }

    // set a function to combine the return values from all connected slots
    // to one single return value
    // This function may be a static or a member function
    void SetCombineFunction(cCall<bool, ret_type*, ret_type> i_Callback, ret_type r_DefaultRetVal)
    {
        mi_Combine        = i_Callback;
        mr_DefaultCombine = r_DefaultRetVal;
    }

    // fires an event. All connected slots will be fired
    // if the combine function returns false, no more slots are fired
    // if the interval since the last fire event has not yet elapsed,
    // the default return value is returned which was set in SetMinInterval()
    ret_type Fire()
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire()))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire(Arg1)))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire(Arg1, Arg2)))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire(Arg1, Arg2, Arg3)))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire(Arg1, Arg2, Arg3, Arg4)))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4, tArg5 Arg5)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance     = true;
        ret_type r_Result = mr_DefaultCombine;

        for (tIter i=mi_List.begin(); i!=mi_List.end(); i++)
        {
            if (!mi_Combine.Execute(&r_Result, (*i)->Fire(Arg1, Arg2, Arg3, Arg4, Arg5)))
                break;
        }
        mb_Reentrance = false;
        return r_Result;
    }
};

template <class cInstance, class tRet, class tArg1=UNUSABLE,
                                       class tArg2=UNUSABLE,
                                       class tArg3=UNUSABLE,
                                       class tArg4=UNUSABLE,
                                       class tArg5=UNUSABLE>
class cSlot
    : public cSigSlotBase<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>
{
private:
    typedef tRet (cInstance::*tFunction0)();
    typedef tRet (cInstance::*tFunction1)(tArg1);
    typedef tRet (cInstance::*tFunction2)(tArg1, tArg2);
    typedef tRet (cInstance::*tFunction3)(tArg1, tArg2, tArg3);
    typedef tRet (cInstance::*tFunction4)(tArg1, tArg2, tArg3, tArg4);
    typedef tRet (cInstance::*tFunction5)(tArg1, tArg2, tArg3, tArg4, tArg5);

    // Choose the correct argument count
    typedef typename CLASS_SWITCH(IS_USABLE(tArg5), tFunction5, tFunction4)  tFunctionA;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg4), tFunctionA, tFunction3)  tFunctionB;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg3), tFunctionB, tFunction2)  tFunctionC;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg2), tFunctionC, tFunction1)  tFunctionD;
    typedef typename CLASS_SWITCH(IS_USABLE(tArg1), tFunctionD, tFunction0)  tFunction;

    cCall<tRet, tArg1, tArg2, tArg3, tArg4, tArg5> mi_CallFire;

protected:
    // to check if the user forgot to call AssignFunction() (see comment above!)
    bool Valid()
    {
        return mi_CallFire.Valid();
    }

public:

    // constructor (see comment above!)
    cSlot(ret_type r_DefaultReenter = (ret_type) 0)
    {
        mr_DefaultReenter = r_DefaultReenter;
        mb_Reentrance     = false;

        mps8_MyName = "Uninitialized-Slot";
        me_Type     = E_Slot;
    }

    // sets the callback to a C++ member function to be executed when Fire() is called (see comment above!)
    void AssignFunction(cInstance *p_Inst, tFunction p_Func, char *ps8_Name = "NoName-Slot")
    {
        mi_CallFire = cCallGen<cInstance, tRet, tArg1, tArg2, tArg3, tArg4, tArg5>(p_Inst, p_Func);

        if (mi_CallFire.Valid()) mps8_MyName = ps8_Name;
    }

    // sets the callback to a static function to be executed when Fire() is called (see comment above!)
    void AssignFunction(tFunction p_Func, char *ps8_Name = "NoName-Slot")
    {
        mi_CallFire = cCallGenS<tRet, tArg1, tArg2, tArg3, tArg4, tArg5>(p_Func);

        if (mi_CallFire.Valid()) mps8_MyName = ps8_Name;
    }

    // fires this slot ( = calls the attached callback function)
    // if the interval since last fire event has not yet elapsed,
    // it returns the default value which has been set in SetMinInterval()
    ret_type Fire()
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute();

        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute(Arg1);

        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute(Arg1, Arg2);

        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute(Arg1, Arg2, Arg3);

        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute(Arg1, Arg2, Arg3, Arg4);

        mb_Reentrance = false;
        return r_Result;
    }

    ret_type Fire(tArg1 Arg1, tArg2 Arg2, tArg3 Arg3, tArg4 Arg4, tArg5 Arg5)
    {
        if (mb_Reentrance)    return mr_DefaultReenter;
        if (!CheckInterval()) return mr_DefaultInterval;

        mb_Reentrance = true;
        ret_type r_Result = mi_CallFire.Execute(Arg1, Arg2, Arg3, Arg4, Arg5);

        mb_Reentrance = false;
        return r_Result;
    }
};


