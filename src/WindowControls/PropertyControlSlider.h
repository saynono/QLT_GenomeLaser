//
//  PropertyControlSlider.h
//  QLT_GenomeLaser
//
//  Created by say nono on 05.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Property/BaseProperty.h"
#include "Gwen/Controls/Property/Text.h"
#include "Gwen/Controls/SplitterBar.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;


namespace Gwen {
    namespace Controls{

class GWEN_EXPORT PropertyControlSlider : public Base {
    
    public:
        
        GWEN_CONTROL( PropertyControlSlider, Base );
        
        virtual Label* GetLabel() { return m_Label; }
//        virtual void SetProperty( Gwen::Controls::HorizontalSlider* prop );
        virtual Controls::Base* GetProperty() { return m_Property; }
        
        virtual void Layout( Gwen::Skin::Base* skin );
        virtual void Render( Gwen::Skin::Base* skin );
    
        void AddSlider(float val, float minVal, float maxVal);
        
        virtual bool IsEditing() { return m_Property && m_Property->IsHovered(); }
        virtual bool IsHovered() { return BaseClass::IsHovered() || ( m_Property && m_Property->IsHovered() ); }
        virtual void OnMouseClickLeft( int x, int y, bool bDown );
    
        virtual void OnEditingChanged();
        virtual void OnHoverChanged();
    
        Gwen::Controls::HorizontalSlider* GetSlider(){ return m_Property; };
    
//        Gwen::Event::Caller	onChange;
//        Gwen::Event::Caller	onPress;
    
    protected:
        
        void OnValueChanged( Gwen::Controls::Base* control );
        
        Label*			m_Label;
        Label*			m_LabelValue;
        Controls::HorizontalSlider*	m_Property;
        
        bool			m_bLastEditing;
        bool			m_bLastHover;
        
};
    
    
}
}




