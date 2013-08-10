//
//  PropertyControlSlider.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 05.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PropertyControlSlider.h"

	
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/Properties.h"
#include "Gwen/Utility.h"

using namespace Gwen;
using namespace Gwen::Controls;


class PropertyRowSliderLabel : public Label
{
    GWEN_CONTROL_INLINE( PropertyRowSliderLabel, Label )
    {
        SetAlignment( Pos::Left | Pos::CenterV );
        m_pPropertyRow = NULL;
    }
    
    void UpdateColours()
    {
        if ( IsDisabled() )										{ return SetTextColor( GetSkin()->Colors.Button.Disabled ); }
        
        if ( m_pPropertyRow && m_pPropertyRow->IsEditing() )	{ return SetTextColor( GetSkin()->Colors.Properties.Label_Selected ); }
        
        if ( m_pPropertyRow && m_pPropertyRow->IsHovered() )	{ return SetTextColor( GetSkin()->Colors.Properties.Label_Hover ); }
        
        SetTextColor( GetSkin()->Colors.Properties.Label_Normal );
    }
    
    void SetPropertyRow( PropertyControlSlider* p ) { m_pPropertyRow = p; }
    
//    void OnMouseClickLeft( int x, int y, bool bDown ){
//        console() << "Click!" << std::endl;
//    }

protected:
    
//    Gwen::Event::Caller	onPress;
    PropertyControlSlider*	m_pPropertyRow;
    
};


GWEN_CONTROL_CONSTRUCTOR( PropertyControlSlider )
{
    
	m_Property = NULL;
	PropertyRowSliderLabel* pLabel = new PropertyRowSliderLabel( this );
	pLabel->SetPropertyRow( this );
	pLabel->Dock( Pos::Left );
	pLabel->SetAlignment( Pos::Left | Pos::Top );
//	pLabel->SetMargin( Margin( 2, 2, 0, 0 ) );
	m_Label = pLabel;
    
}

void PropertyControlSlider::Render( Gwen::Skin::Base* skin )
{
	/* SORRY */
	if ( IsEditing() != m_bLastEditing )
	{
		OnEditingChanged();
		m_bLastEditing = IsEditing();
	}
    
	if ( IsHovered() != m_bLastHover )
	{
		OnHoverChanged();
		m_bLastHover = IsHovered();
	}
    
	/* SORRY */
	skin->DrawPropertyRow( this, m_Label->Right(), IsEditing(), IsHovered() | m_Property->IsHovered() );
}

void PropertyControlSlider::Layout( Gwen::Skin::Base* /*skin*/ )
{
	Properties* pParent = gwen_cast<Properties> ( GetParent() );
    
	if ( !pParent ) { return; }
    
	m_Label->SetWidth( pParent->GetSplitWidth() );
    
	if ( m_Property )
	{
		SetHeight( m_Property->Height() );
	}
}

void PropertyControlSlider::AddSlider(float val, float minVal, float maxVal){
    
    val = Clamp(val, minVal, maxVal);
    Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( this );
//    pSlider->SetPos( 70, 0 );
    pSlider->SetSize( 200, 30 );
    pSlider->SetRange( minVal, maxVal );
    pSlider->SetFloatValue( val );
    pSlider->SetName("SLIDER YEAH");
//    pSlider->SetPadding( Padding( 10, 2, 10, 0 ) );
    //        pSlider->SetParent( this );
    pSlider->Dock( Gwen::Pos::Left );
    pSlider->SetMargin( Margin( 10, 0, 0, 0 ) );
    m_Property = pSlider;

    
    PropertyRowSliderLabel* pLabel = new PropertyRowSliderLabel( this );
	pLabel->SetPropertyRow( this );
    pLabel->SetSize(100, 30);
	pLabel->Dock( Pos::Left );
	pLabel->SetAlignment( Pos::Right | Pos::Top );
	pLabel->SetMargin( Margin( 10, 0, 0, 0 ) );
    //	pLabel->SetMargin( Margin( 2, 2, 0, 0 ) );
    pLabel->SetValue( toString(val) );
	m_LabelValue = pLabel;
    
    
    Gwen::Controls::CheckBox* pCheck = new Gwen::Controls::CheckBox( this );
	pCheck->Dock( Pos::Left );
	pCheck->SetAlignment( Pos::Right | Pos::Top );
	pCheck->SetMargin( Margin( 10, 0, 0, 0 ) );
    
    Gwen::Controls::Button* pButton = new Gwen::Controls::Button( this );
	pButton->Dock( Pos::Left );
    pButton->SetText( "INPUT" );
	pButton->SetAlignment( Pos::Right | Pos::Top );
	pButton->SetMargin( Margin( 10, 0, 0, 0 ) );
    m_ListenButton = pButton;


    pSlider->onValueChanged.Add( this, &PropertyControlSlider::OnValueChanged );


}

void PropertyControlSlider::OnValueChanged( Gwen::Controls::Base* pControl ){
    
    Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
    float val = pSlider->GetFloatValue();
    m_LabelValue->SetValue( toString(val) );    
    
}

void PropertyControlSlider::OnEditingChanged()
{
	m_Label->Redraw();
}

void PropertyControlSlider::OnHoverChanged()
{
	m_Label->Redraw();
}

void PropertyControlSlider::OnMouseClickLeft( int x, int y, bool bDown ){
    console() << "Click!" << std::endl;
}

void PropertyControlSlider::setFloatValue( float val ){
    m_Property->SetFloatValue( val );
    
}

float PropertyControlSlider::getFloatValue(){
    
}

