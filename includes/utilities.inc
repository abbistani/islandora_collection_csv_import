<?php

/**
 * @file
 * Creates Islandora Entity Objects from CSV.
 */

/**
 * Created Entities from supplied csv file.
 *
 * @param url $path
 *   Path to file
 * @param string $collection_pid
 *   PID of collection where created objects are to be stored.
 */
function islandora_collection_import_csv_batch($path) {
  $collections = islandora_collection_read_csv($path);
  $batch = array(
    'title' => t("Creating Collection Objects"),
    'progress_message' => t('Adding @current collection out of @total.'),
    'operations' => array(),
    'file' => drupal_get_path('module', 'islandora_collection_csv_import') . '/includes/utilities.inc',
  );
  foreach ($collections as $collection) {
    $batch['operations'][] = array(
      'islandora_collection_csv_import_build_collection_object',
      array($collection),
    );
  }
  batch_set($batch);
}

/**
 * Creates associative array representing scholar data.
 *
 * @param url $path
 *   Path to CSV file
 *
 * @return array
 *   array of associative arrays containing header => value pairs
 */
function islandora_collection_read_csv($path) {
  ini_set("auto_detect_line_endings", "1");
  $collections = array();
  if (($handle = fopen($path, "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 0, ",")) !== FALSE) {
      if (!isset($header)) {
        $header = $data;
        continue;
      }
      for ($counter = 0; $counter < count($data); $counter++) {
        $collection[$header[$counter]] = $data[$counter];
      }
      $collections[] = $collection;
    }
    fclose($handle);
  }
  return $collections;
}

/**
 * Builds scholar objects.
 *
 * @param array $collection
 *   Header => value pairs representing date to be converted to MADS record
 * @param string $collection_pid
 *   PID of collection to hold new objects.
 */
function islandora_collection_csv_import_build_collection_object($collection) {

  $tuque = new IslandoraTuque();
  $repository = $tuque->repository;
  $fedora_object = $repository->constructObject($collection['PID']);
  $fedora_object->label = isset($collection['LABEL']) ? htmlspecialchars(str_replace('||', ',', $collection['LABEL'])) : 'Label';
  $fedora_object->owner = 'admin';
  $fedora_object->relationships->add(FEDORA_MODEL_URI, 'hasModel', 'islandora:collectionCModel');
  $parents = explode('~', $collection['PARENT']);
  foreach ($parents as $parent) {
    $fedora_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOfCollection', $parent);
  }
  if (isset($collection['COLLECTION_POLICY'])) {
    $collection_policy_ds = $fedora_object->constructDatastream('COLLECTION_POLICY', 'X');
    $collection_policy_ds->label = 'Collection policy';
    $collection_policy_ds->mimetype = 'text/xml';
    $collection_policy_ds->setContentFromFile($collection['COLLECTION_POLICY']);
    $fedora_object->ingestDatastream($collection_policy_ds); 
  }  
  $new_fedora_object = islandora_add_object($fedora_object);
}
