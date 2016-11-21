# scp training_organic_nitrogen.csv rwu@134.197.20.79:/cse/home/rwu/Desktop/hadoop/sparkdata
# scp rwu@134.197.20.79:/cse/home/rwu/Desktop/hadoop/sparkdata/result.csv /home/rwu/Desktop/data



input_file = "data.csv"
output_file = "test.libsvm"

import pandas as pd
import math
import subprocess
import sys
import csv
import os
from collections import defaultdict
import json
def construct_line( label, line ):
	new_line = []
	if float( label ) == 0.0:
		label = "0"
	new_line.append( label )
	for i, item in enumerate( line ):
		if item == '' or float( item ) == 0.0:
			continue
		new_item = "%s:%s" % ( i + 1, item )
		new_line.append( new_item )
	new_line = " ".join( new_line )
	new_line += "\n"
	return new_line

def convert_csv_into_libsvm(input_file,output_file,label_index=0,skip_headers=True):
	'''
	the function converts csv into libsvm
	'''
	i = open( input_file, 'rb' )
	o = open( output_file, 'wb' )
	reader = csv.reader( i )
	if skip_headers:
		headers = reader.next()
	for line in reader:
		if label_index == -1:
			label = '1'
		else:
			label = line.pop( label_index )
		new_line = construct_line( label, line )
		o.write( new_line )

convert_csv_into_libsvm(input_file,output_file)

from pyspark.ml.regression import GeneralizedLinearRegression
from pyspark.ml.evaluation import RegressionEvaluator
from pyspark.sql import SQLContext
from pyspark import SparkContext
import json
import sys

sqlContext = SQLContext(sc)
filename = output_file

dataset = sqlContext.read.format("libsvm").load(filename)
(trainingData, testData) = dataset.randomSplit([0.7, 0.3])

glr = GeneralizedLinearRegression(family="gaussian", link="identity", maxIter=10, regParam=0.3)

# Fit the model
model = glr.fit(trainingData)

# Print the coefficients and intercept for generalized linear regression model
print("\n\n\n\nCoefficients: " + str(model.coefficients))
print("Intercept: " + str(model.intercept))

# Summarize the model over the training set and print out some metrics
summary = model.summary

summary.residuals().show()

predictions = model.transform(testData)
evaluator = RegressionEvaluator(
    labelCol="label", predictionCol="prediction", metricName="rmse")

rmse = evaluator.evaluate(predictions)
print "Root Mean Squared Error (RMSE) on test data = "+str(rmse)




