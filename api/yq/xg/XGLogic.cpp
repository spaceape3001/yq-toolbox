////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XGLogic.hpp"
#include <yq/xg/XGElementMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::XGLogic)

namespace yq {
    void XGLogic::init_meta()
    {
        auto w = writer<XGLogic>();
        w.description("Base for logic/conditionals");
        w.abstract();
    }

    XGLogic::XGLogic()
    {
    }
    
    XGLogic::~XGLogic()
    {
    }
}
