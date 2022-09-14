<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt16 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('int16', $name);
		}

	}