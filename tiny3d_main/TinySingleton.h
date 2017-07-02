//
//  TinySingleton.h
//  proj_mac
//
//  Created by reuben chao on 2/5/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#ifndef proj_mac_TinySingleton_h
#define proj_mac_TinySingleton_h

#include <assert.h>

namespace Tiny
{
    template <typename T> class TinySingleton
    {
    private:
        /** \brief Explicit private copy constructor. This is a forbidden operation.*/
        TinySingleton(const TinySingleton<T> &);
        
        /** \brief Private operator= . This is a forbidden operation. */
        TinySingleton& operator=(const TinySingleton<T> &);
        
    protected:
        
        static T* msSingleton;
        
    public:
        TinySingleton( void )
        {
            //assert( !msSingleton );
            //msSingleton = static_cast< T* >( this );
        }
        ~TinySingleton( void )
        {  assert( msSingleton );  msSingleton = nullptr;  }
        static T* getSingleton( void )
        {
            if (msSingleton == nullptr)
            {
                msSingleton = new T();
            }
            return msSingleton;
        }
    };
    
    template <typename T>
    T* TinySingleton<T>::msSingleton = nullptr;
    /** @} */
    /** @} */
}

#endif
