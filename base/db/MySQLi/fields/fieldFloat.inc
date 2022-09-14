<?php

	namespace Base\DB;

	use Base\DB;

	class FieldFloat extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('float', $name);
		}

	}