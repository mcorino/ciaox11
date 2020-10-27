/**
 * @file    main.cpp
 * @author  Marcel Smit
 *
 * @brief   Testing the ddsx11 logging formatters.
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */

#include "idl/dds_dcpsC.h"
#include <iostream>
#include "tests/testlib/ddsx11_testlog.h"

class MyEntity
  : public IDL::traits<DDS::Entity>::base_type
{
public:
  DDS::ReturnCode_t enable() override
  {
    return ::DDS::RETCODE_OK;
  }

  IDL::traits<DDS::StatusCondition>::ref_type get_statuscondition() override
  {
    return {};
  }

  DDS::StatusMask get_status_changes() override
  {
    return DDS::LIVELINESS_LOST_STATUS;
  }

  DDS::InstanceHandle_t get_instance_handle() override
  {
#if defined DDSX11_NDDS
    return DDS::InstanceHandle_t {{{15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}}, 16, false};
#else
    return DDS::InstanceHandle_t {{0}};
#endif
  }
};

int main (int, char **)
{
  std::ostringstream ostr;

  ::DDS::QosPolicyCountSeq policy_count_seq;
#if defined DDSX11_NDDS
  ::DDS::QosPolicyCount const policy_count (::DDS::DOMAINPARTICIPANTRESOURCELIMITS_QOS_POLICY_ID, 5);
  DDSX11_TEST_DEBUG << "Logging QosPolicyCount : " << DDS::dds_write (policy_count) << std::endl;
  ostr << "Logging QosPolicyCount : " << DDS::dds_write (policy_count) << std::endl;

  policy_count_seq.push_back (policy_count);
  policy_count_seq.push_back (policy_count);
  policy_count_seq.push_back (policy_count);
  DDSX11_TEST_DEBUG << "Logging QosPolicyCountSeq : " << DDS::dds_write (policy_count_seq) << std::endl;
  ostr << "Logging QosPolicyCountSeq : " << DDS::dds_write (policy_count_seq) << std::endl;
#endif /* DDSX11_NDDS */

  ::DDS::Time_t const time (15, 0);
  DDSX11_TEST_DEBUG << "Logging Time_t : " << DDS::dds_write (time) << std::endl;
  ostr << "Logging Time_t : " << DDS::dds_write (time) << std::endl;

#if defined DDSX11_NDDS
  ::DDS::StatusKind const status_kind (::DDS::RELIABLE_WRITER_CACHE_CHANGED_STATUS);
  DDSX11_TEST_DEBUG << "Logging StatusKind : " << DDS::dds_write (status_kind) << std::endl;
  ostr << "Logging StatusKind : " << DDS::dds_write (status_kind) << std::endl;
#endif /* DDSX11_NDDS */

#if defined DDSX11_NDDS
  DDS::InstanceHandle_t const instance_handle ({{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}}, 16, true);
#else
  DDS::InstanceHandle_t const instance_handle {{6}};
#endif /* DDSX11_NDDS */
  DDSX11_TEST_DEBUG << "Logging InstanceHandle_t : " << DDS::dds_write(instance_handle) << std::endl;
  ostr << "Logging InstanceHandle_t : " << DDS::dds_write(instance_handle) << std::endl;

  IDL::traits<DDS::Entity>::ref_type entity = CORBA::make_reference<MyEntity>();
  DDSX11_TEST_DEBUG << "Logging DDS::Entity : " << DDS::dds_write (entity) << std::endl;
  ostr << "Logging DDS::Entity : " << DDS::dds_write (entity) << std::endl;

#if defined DDSX11_NDDS
  DDS::SampleLostStatus const sample_lost_status (5, 10, ::DDS::SampleLostStatusKind::NOT_LOST);
#else
  DDS::SampleLostStatus const sample_lost_status (5, 10);
#endif
  DDSX11_TEST_DEBUG << "Logging DDS::SampleLostStatus : " << DDS::dds_write (sample_lost_status) << std::endl;
  ostr << "Logging DDS::SampleLostStatus : " << DDS::dds_write (sample_lost_status) << std::endl;

  DDS::RequestedDeadlineMissedStatus const requested_deadline_missed_status (6, 11, instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::RequestedDeadlineMissedStatus : "
    << DDS::dds_write (requested_deadline_missed_status) << std::endl;
  ostr << "Logging DDS::RequestedDeadlineMissedStatus : "
    << DDS::dds_write (requested_deadline_missed_status) << std::endl;

  DDS::InconsistentTopicStatus const inconsistent_topic_status (10, 15);
  DDSX11_TEST_DEBUG << "Logging DDS::InconsistentTopicStatus : "
    << DDS::dds_write (inconsistent_topic_status) << std::endl;
  ostr << "Logging DDS::InconsistentTopicStatus : "
    << DDS::dds_write (inconsistent_topic_status) << std::endl;

  DDS::RequestedIncompatibleQosStatus const requested_incompatible_qos_status (
    11, 16, ::DDS::ENTITYFACTORY_QOS_POLICY_ID, policy_count_seq);
  DDSX11_TEST_DEBUG << "Logging DDS::RequestedIncompatibleQosStatus : "
    << DDS::dds_write (requested_incompatible_qos_status) << std::endl;
  ostr << "Logging DDS::RequestedIncompatibleQosStatus : "
    << DDS::dds_write (requested_incompatible_qos_status) << std::endl;

  DDS::SampleRejectedStatus const sample_rejected_status (15, 20,
    DDS::SampleRejectedStatusKind::REJECTED_BY_SAMPLES_LIMIT,
    instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::SampleRejectedStatus : "
    << DDS::dds_write (sample_rejected_status) << std::endl;
  ostr << "Logging DDS::SampleRejectedStatus : "
    << DDS::dds_write (sample_rejected_status) << std::endl;

  DDS::OfferedDeadlineMissedStatus const offered_deadline_missed_status (7, 12, instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::OfferedDeadlineMissedStatus : "
    << DDS::dds_write (offered_deadline_missed_status) << std::endl;
  ostr << "Logging DDS::OfferedDeadlineMissedStatus : "
    << DDS::dds_write (offered_deadline_missed_status) << std::endl;

#if defined DDSX11_NDDS
  DDS::OfferedIncompatibleQosStatus const offered_incompatible_qos_status (
    12, 17, ::DDS::DATAWRITERRESOURCELIMITS_QOS_POLICY_ID, policy_count_seq);
  DDSX11_TEST_DEBUG << "Logging DDS::OfferedIncompatibleQosStatus : "
    << DDS::dds_write (offered_incompatible_qos_status) << std::endl;
  ostr << "Logging DDS::OfferedIncompatibleQosStatus : "
    << DDS::dds_write (offered_incompatible_qos_status) << std::endl;
#endif /* DDSX11_NDDS */

  DDS::PublicationMatchedStatus const publication_matched_status (
    20, 15, 12, 7, instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::PublicationMatchedStatus : "
    << DDS::dds_write (publication_matched_status) << std::endl;
  ostr << "Logging DDS::PublicationMatchedStatus : "
    << DDS::dds_write (publication_matched_status) << std::endl;

  DDS::SubscriptionMatchedStatus const subscription_matched_status (
    7, 12, 15, 20, instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::SubscriptionMatchedStatus : "
    << DDS::dds_write (subscription_matched_status) << std::endl;
  ostr << "Logging DDS::SubscriptionMatchedStatus : "
    << DDS::dds_write (subscription_matched_status) << std::endl;

  DDS::LivelinessLostStatus const liveliness_lost_status (8, 13);
  DDSX11_TEST_DEBUG << "Logging DDS::LivelinessLostStatus : "
    << DDS::dds_write (liveliness_lost_status) << std::endl;
  ostr << "Logging DDS::LivelinessLostStatus : "
    << DDS::dds_write (liveliness_lost_status) << std::endl;

  DDS::LivelinessChangedStatus const liveliness_changed_status (
    9, 14, 16, 21, instance_handle);
  DDSX11_TEST_DEBUG << "Logging DDS::LivelinessChangedStatus : "
    << DDS::dds_write (liveliness_changed_status) << std::endl;
  ostr << "Logging DDS::LivelinessChangedStatus : "
    << DDS::dds_write (liveliness_changed_status) << std::endl;

  DDS::Duration_t const duration (134, 31145112);
  DDSX11_TEST_DEBUG << "Logging DDS::Duration_t : "
    << DDS::dds_write (duration) << std::endl;
  ostr << "Logging DDS::Duration_t : "
    << DDS::dds_write (duration) << std::endl;

#if defined DDSX11_NDDS
  DDS::QosPolicyId_t const policy_id (DDS::DOMAINPARTICIPANTRESOURCELIMITS_QOS_POLICY_ID);
  DDSX11_TEST_DEBUG << "Logging DDS::QosPolicyId_t : "
    << DDS::dds_write (policy_id) << std::endl;
  ostr << "Logging DDS::QosPolicyId_t : "
    << DDS::dds_write (policy_id) << std::endl;
#endif /* DDSX11_NDDS */

  DDS::StatusMask const mask_pub_match { DDS::PUBLICATION_MATCHED_STATUS };
  DDS::StatusMask const mask_pub_data_match { DDS::PUBLICATION_MATCHED_STATUS | DDS::DATA_ON_READERS_STATUS };
  DDS::StatusMask const mask_all { DDS::STATUS_MASK_ALL };
  DDS::StatusMask const mask_none { DDS::STATUS_MASK_NONE };

  DDSX11_TEST_DEBUG << "Logging mask pub: "
    << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask_pub_match) << std::endl;
  DDSX11_TEST_DEBUG << "Logging mask pub data: "
    << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask_pub_data_match) << std::endl;
  DDSX11_TEST_DEBUG << "Logging mask all: "
    << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask_all) << std::endl;
  DDSX11_TEST_DEBUG << "Logging mask none: "
    << IDL::traits< ::DDS::StatusMask>::write<status_mask_formatter> (mask_none) << std::endl;

  return 0;
}