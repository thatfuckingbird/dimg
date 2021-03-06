/*****************************************************************
|
|   Platinum - Managed MediaServerEventBridge
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
|
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc.,
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "StdAfx.h"
#include "MediaServerEventBridge.h"
#include "MediaServer.h"
#include "Action.h"

NPT_Result Platinum::MediaServerEventBridge::OnBrowseMetadata(PLT_ActionReference&          action,
                                                              const char*                   object_id,
                                                              const char*                   filter,
                                                              NPT_UInt32                    starting_index,
                                                              NPT_UInt32                    requested_count,
                                                              const char*                   sort_criteria,
                                                              const PLT_HttpRequestContext& context)
{
    return m_pMediaServer->OnBrowseMetadataDelegate(marshal_as<Action^>(action),
                                                    marshal_as<String^>(object_id),
                                                    marshal_as<String^>(filter),
                                                    starting_index,
                                                    requested_count,
                                                    marshal_as<String^>(sort_criteria),
                                                    marshal_as<HttpRequestContext^>(context));
}

NPT_Result Platinum::MediaServerEventBridge::OnBrowseDirectChildren(PLT_ActionReference&          action,
                                                                    const char*                   object_id,
                                                                    const char*                   filter,
                                                                    NPT_UInt32                    starting_index,
                                                                    NPT_UInt32                    requested_count,
                                                                    const char*                   sort_criteria,
                                                                    const PLT_HttpRequestContext& context)
{
    return m_pMediaServer->OnBrowseDirectChildrenDelegate(marshal_as<Action^>(action),
                                                          marshal_as<String^>(object_id),
                                                          marshal_as<String^>(filter),
                                                          starting_index,
                                                          requested_count,
                                                          marshal_as<String^>(sort_criteria),
                                                          marshal_as<HttpRequestContext^>(context));
}

NPT_Result Platinum::MediaServerEventBridge::OnSearchContainer(PLT_ActionReference&          action,
                                                               const char*                   object_id,
                                                               const char*                   search_criteria,
                                                               const char*                   filter,
                                                               NPT_UInt32                    starting_index,
                                                               NPT_UInt32                    requested_count,
                                                               const char*                   sort_criteria,
                                                               const PLT_HttpRequestContext& context)
{

    return m_pMediaServer->OnSearchContainerDelegate(marshal_as<Action^>(action),
                                                     marshal_as<String^>(object_id),
                                                     marshal_as<String^>(search_criteria),
                                                     marshal_as<String^>(filter),
                                                     starting_index,
                                                     requested_count,
                                                     marshal_as<String^>(sort_criteria),
                                                     marshal_as<HttpRequestContext^>(context));
}

NPT_Result Platinum::MediaServerEventBridge::ProcessFileRequest(NPT_HttpRequest&              request,
                                                                const NPT_HttpRequestContext& context,
                                                                NPT_HttpResponse&             response)
{
    PLT_HttpRequestContext _context(request, context);
    return m_pMediaServer->OnProcessFileRequestDelegate(marshal_as<HttpRequestContext^>(_context),
                                                        marshal_as<HttpResponse^>(response));
}
