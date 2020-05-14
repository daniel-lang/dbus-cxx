/***************************************************************************
 *   Copyright (C) 2020 by Robert Middleton                                *
 *   robert.middleton@rm5248.com                                           *
 *                                                                         *
 *   This file is part of the dbus-cxx library.                            *
 *                                                                         *
 *   The dbus-cxx library is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The dbus-cxx library is distributed in the hope that it will be       *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#include <dbus-cxx/variant.h>
#include <dbus-cxx/messageiterator.h>
#include <dbus-cxx/marshaling.h>
#include <dbus-cxx/dbus-cxx-private.h>
#include <stdint.h>
#include "enums.h"
#include "path.h"
#include "signature.h"

namespace DBus { class FileDescriptor; }

using DBus::Variant;

class Variant::priv_data {
public:
    priv_data() :
        m_currentType( DataType::INVALID )
    {}

    priv_data( uint8_t byte ) :
        m_currentType( DataType::BYTE ),
        m_signature( DBus::signature( byte ) ),
        m_data( byte ),
        m_dataAlignment( 1 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( byte );
    }

    priv_data( bool b ) :
        m_currentType( DataType::BOOLEAN ),
        m_signature( DBus::signature( b ) ),
        m_data( b ),
        m_dataAlignment( 4 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( b );
    }

    priv_data( int16_t i ) :
        m_currentType( DataType::INT16 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 2 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( uint16_t i ) :
        m_currentType( DataType::UINT16 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 2 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( int32_t i ) :
        m_currentType( DataType::INT32 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 4 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( uint32_t i ) :
        m_currentType( DataType::UINT32 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 4 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( int64_t i ) :
        m_currentType( DataType::INT64 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 8 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

   priv_data( uint64_t i ) :
        m_currentType( DataType::UINT64 ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 8 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( double i ) :
        m_currentType( DataType::DOUBLE ),
        m_signature( DBus::signature( i ) ),
        m_data( i ),
        m_dataAlignment( 8 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( i );
    }

    priv_data( const char* cstr ) :
        priv_data( std::string( cstr ) ){}

    priv_data( std::string str ) :
        m_currentType( DataType::STRING ),
        m_signature( DBus::signature( str ) ),
        m_data( str ),
        m_dataAlignment( 4 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( str );
    }

    priv_data( DBus::Signature sig ) :
        m_currentType( DataType::SIGNATURE ),
        m_signature( DBus::signature( sig ) ),
        m_data( sig ),
        m_dataAlignment( 1 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( sig );
    }

    priv_data( DBus::Path path ) :
        m_currentType( DataType::OBJECT_PATH ),
        m_signature( DBus::signature( path ) ),
        m_data( path ),
        m_dataAlignment( 4 )
    {
        Marshaling marshal( &m_marshaled, Endianess::Big );
        marshal.marshal( path );
    }

    priv_data( std::shared_ptr<FileDescriptor> fd ) :
        m_currentType( DataType::UNIX_FD ),
        m_signature( DBus::signature( fd ) ),
        m_data( fd ),
        m_dataAlignment( 4 )
    {}

//    priv_data( const priv_data& other ) = default;
//    priv_data( const priv_data& other ) :
//        m_currentType( other.m_currentType ),
//        m_signature( other.m_signature ),
//        m_data( other.m_data ),
//        m_marshaled( other.m_marshaled ),
//        m_dataAlignment( other.m_dataAlignment ) {
//    }

public:
    DataType m_currentType;
    Signature m_signature;
    std::any m_data;
    std::vector<uint8_t> m_marshaled;
    int m_dataAlignment;
};

Variant::Variant() :
    m_priv( std::make_unique<priv_data>() )
{}

Variant::Variant( uint8_t byte ) :
    m_priv( std::make_unique<priv_data>( byte ) )
{}

Variant::Variant( bool b ) :
    m_priv( std::make_unique<priv_data>( b ) )
{}

Variant::Variant( int16_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( uint16_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( int32_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( uint32_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( int64_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( uint64_t i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( double i ) :
    m_priv( std::make_unique<priv_data>( i ) )
{}

Variant::Variant( const char* cstr ) :
    Variant( std::string( cstr ) ){}

Variant::Variant( std::string str ) :
    m_priv( std::make_unique<priv_data>( str ) )
{}

Variant::Variant( DBus::Signature sig ) :
    m_priv( std::make_unique<priv_data>( sig ) )
{}

Variant::Variant( DBus::Path path ) :
    m_priv( std::make_unique<priv_data>( path ) )
{}

Variant::Variant( std::shared_ptr<FileDescriptor> fd ) :
    m_priv( std::make_unique<priv_data>( fd ) )
{}

Variant::Variant( const Variant& other ) :
    m_priv( std::make_unique<priv_data>( *other.m_priv ) )
{}

Variant::~Variant(){}

DBus::Signature Variant::signature() const {
    return m_priv->m_signature;
}

DBus::DataType Variant::currentType() const {
    return m_priv->m_currentType;
}

std::any Variant::value() const {
    return m_priv->m_data;
}

DBus::Variant Variant::createFromMessage( MessageIterator iter ){
    std::string signature = iter.signature();
    if( signature == DBUSCXX_TYPE_BYTE_AS_STRING ){
        return Variant( (uint8_t)iter );
    }
    if( signature == DBUSCXX_TYPE_BOOLEAN_AS_STRING ){
        return Variant( (bool)iter );
    }
    if( signature == DBUSCXX_TYPE_INT16_AS_STRING ){
        return Variant( (int16_t)iter );
    }
    if( signature == DBUSCXX_TYPE_UINT16_AS_STRING ){
        return Variant( (uint16_t)iter );
    }
    if( signature == DBUSCXX_TYPE_INT32_AS_STRING ){
        return Variant( (int32_t)iter );
    }
    if( signature == DBUSCXX_TYPE_UINT32_AS_STRING ){
        return Variant( (uint32_t)iter );
    }
    if( signature == DBUSCXX_TYPE_INT64_AS_STRING ){
        return Variant( (int64_t)iter );
    }
    if( signature == DBUSCXX_TYPE_UINT64_AS_STRING ){
        return Variant( (uint64_t)iter );
    }
    if( signature == DBUSCXX_TYPE_DOUBLE_AS_STRING ){
        return Variant( (double)iter );
    }
    if( signature == DBUSCXX_TYPE_STRING_AS_STRING ){
        return Variant( (std::string)iter );
    }
    if( signature == DBUSCXX_TYPE_SIGNATURE_AS_STRING ){
        return Variant( (Signature)iter );
    }
    if( signature == DBUSCXX_TYPE_OBJECT_PATH_AS_STRING ){
        return Variant( (Path)iter );
    }
    if( signature == DBUSCXX_TYPE_VARIANT_AS_STRING ){
        return DBUSCXX_MESSAGEITERATOR_OPERATOR_VARIANT( iter );
    }
    if( signature == DBUSCXX_TYPE_UNIX_FD_AS_STRING ){
        return Variant( (std::shared_ptr<FileDescriptor>)iter );
    }

    return Variant();
}

const std::vector<uint8_t>* Variant::marshaled() const {
    return &m_priv->m_marshaled;
}

int Variant::data_alignment() const {
    return m_priv->m_dataAlignment;
}

bool Variant::operator==( const Variant& other ) const {
    bool sameType = other.currentType() == currentType();
    bool vectorsEqual = false;

    if( sameType ){
        vectorsEqual = other.m_priv->m_marshaled == m_priv->m_marshaled;
    }

    return sameType && vectorsEqual;
}

Variant& Variant::operator=(const Variant &other) {
    *m_priv = *other.m_priv;

    return *this;
}

namespace DBus {

std::ostream& operator<<( std::ostream& os, const Variant& var ){
    os << "DBus::Variant[" << var.currentType() << "=";
    switch( var.currentType() ){
    case DataType::BYTE:
      os << std::any_cast<uint8_t>( var.value() );
      break;
    case DataType::BOOLEAN:
      os << std::any_cast<bool>( var.value() );
      break;
    case DataType::INT16:
      os << std::any_cast<int16_t>( var.value() );
      break;
    case DataType::UINT16:
      os << std::any_cast<uint16_t>( var.value() );
      break;
    case DataType::INT32:
      os << std::any_cast<int32_t>( var.value() );
      break;
    case DataType::UINT32:
      os << std::any_cast<uint32_t>( var.value() );
      break;
    case DataType::INT64:
      os << std::any_cast<int64_t>( var.value() );
      break;
    case DataType::UINT64:
      os << std::any_cast<uint64_t>( var.value() );
      break;
    case DataType::DOUBLE:
      os << std::any_cast<double>( var.value() );
      break;
    case DataType::STRING:
      os << std::any_cast<std::string>( var.value() );
      break;
    case DataType::OBJECT_PATH:
      os << std::any_cast<Path>( var.value() );
      break;
    case DataType::SIGNATURE:
      os << std::any_cast<Signature>( var.value() );
      break;
    case DataType::ARRAY:
      os << "array TODO";
      break;
    case DataType::VARIANT:
      os << std::any_cast<Variant>( var.value() );
      break;
    case DataType::STRUCT:
      os << "struct TODO";
      break;
    case DataType::DICT_ENTRY:
      os << "dict_entry TODO";
      break;
    case DataType::UNIX_FD:
      os << "unix_fd TODO";
      break;
  case DataType::INVALID:
        break;
    }
    os << "]";
    return os;
}

}
