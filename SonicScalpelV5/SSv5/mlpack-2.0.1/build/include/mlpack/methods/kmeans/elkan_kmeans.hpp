/**
 * @file elkan_kmeans.hpp
 * @author Ryan Curtin
 *
 * An implementation of Elkan's algorithm for exact Lloyd iterations.
 *
 * This file is part of mlpack 2.0.1.
 *
 * mlpack is free software; you may redstribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef __MLPACK_METHODS_KMEANS_ELKAN_KMEANS_HPP
#define __MLPACK_METHODS_KMEANS_ELKAN_KMEANS_HPP

namespace mlpack {
namespace kmeans {

template<typename MetricType, typename MatType>
class ElkanKMeans
{
 public:
  /**
   * Construct the ElkanKMeans object, which must store several sets of bounds.
   */
  ElkanKMeans(const MatType& dataset, MetricType& metric);

  /**
   * Run a single iteration of Elkan's algorithm, updating the given centroids
   * into the newCentroids matrix.
   *
   * @param centroids Current cluster centroids.
   * @param newCentroids New cluster centroids.
   * @param counts Current counts, to be overwritten with new counts.
   */
  double Iterate(const arma::mat& centroids,
                 arma::mat& newCentroids,
                 arma::Col<size_t>& counts);

  size_t DistanceCalculations() const { return distanceCalculations; }

 private:
  //! The dataset.
  const MatType& dataset;
  //! The instantiated metric.
  MetricType& metric;

  //! Holds intra-cluster distances.
  arma::mat clusterDistances;
  //! Half the distance from a cluster to its nearest cluster (s(c)).
  arma::vec minClusterDistances;

  //! Holds the index of the cluster that owns each point.
  arma::Col<size_t> assignments;

  //! Upper bounds on the distance between each point and its closest cluster.
  arma::vec upperBounds;
  //! Lower bounds on the distance between each point and each cluster.
  arma::mat lowerBounds;

  //! Track distance calculations.
  size_t distanceCalculations;
};

} // namespace kmeans
} // namespace mlpack

// Include implementation.
#include "elkan_kmeans_impl.hpp"

#endif