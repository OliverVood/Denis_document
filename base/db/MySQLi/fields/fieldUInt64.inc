<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt64 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('uint64', $name);
		}

	}