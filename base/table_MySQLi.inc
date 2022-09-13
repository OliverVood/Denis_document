<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		public function __construct($name, $dbname) {
			parent::__construct($name, $dbname);
		}

		public function Chek() {
			// TODO: Implement Chek() method.
		}

		public function Make() {
			// TODO: Implement Make() method.
		}

		private function Append($type, $name, $params) {
			$this->structure[$name] = [
				'type' => $type,
				'params' => $params
			];
		}

		public function ID(string $name) {
			$this->Append('id', $name, null);
		}

		public function bool(string $name) {

		}

		public function int8(string $name) {

		}

		public function int16(string $name) {

		}

		public function int24(string $name) {

		}

		public function int32(string $name) {

		}

		public function int64(string $name) {

		}

		public function uint8(string $name) {

		}

		public function uint16(string $name) {

		}

		public function uint24(string $name) {

		}

		public function uint32(string $name) {

		}

		public function uint64(string $name) {

		}

		public function float(string $name) {

		}

		public function double(string $name) {

		}

		public function timestamp(string $name, bool $update = false) {

		}

		public function enum(string $name, array $enum) {

		}

		public function set(string $name, array $set) {

		}

		public function string(string $name, $length) {

		}

		public function text(string $name) {

		}


	}