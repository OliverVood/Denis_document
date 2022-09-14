<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSet extends DB\Field {
		private array $set;

		public function __construct(string $name, array $set) {
			parent::__construct('set', $name);

			$this->set = $set;
		}

	}