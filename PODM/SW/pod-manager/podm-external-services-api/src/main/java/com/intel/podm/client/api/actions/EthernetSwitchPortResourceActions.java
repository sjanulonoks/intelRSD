/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.podm.client.api.actions;

import com.intel.podm.client.api.ExternalServiceApiActionException;
import com.intel.podm.client.api.ExternalServiceApiReaderException;
import com.intel.podm.client.api.resources.redfish.EthernetSwitchPortResource;
import com.intel.podm.client.api.resources.redfish.EthernetSwitchPortVlanResource;

import java.net.URI;

public interface EthernetSwitchPortResourceActions {
    URI createVlan(URI switchPortUri, int vlanId, boolean tagged) throws ExternalServiceApiActionException;
    EthernetSwitchPortVlanResource getVlan(URI vlanUri) throws ExternalServiceApiReaderException;
    void deleteVlan(URI vlanUri) throws ExternalServiceApiActionException;
    URI createSwitchPort(URI switchPortCollectionUri, EthernetSwitchPortResourceCreationRequest creationRequest) throws ExternalServiceApiActionException;
    EthernetSwitchPortResource getSwitchPort(URI switchPortUri) throws ExternalServiceApiReaderException;
    void updateSwitchPort(URI switchPortUri, EthernetSwitchPortResourceModificationRequest modificationRequest) throws ExternalServiceApiActionException;
    void deleteSwitchPort(URI switchPortUri) throws ExternalServiceApiActionException;
}
