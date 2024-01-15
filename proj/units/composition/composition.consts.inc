<?php

	namespace Proj\Units\Consts;

	interface Composition {
		const ID						= ID_COMPOSITION;
		const NAME						= 'composition';
		const TITLE						= 'Композиция';


		const ACCESS_SETTING			= 1;
		const ACCESS_CREATE				= 4;

		const TEXT_ERROR_ACCESS			= 'Ошибка доступа. Недостаточно прав.';

		const FILE_CONTROLLER			= 1;
		const FILE_STRUCTURE			= 2;
		const FILE_ACTIONS				= 4;
		const FILE_MODEL				= 8;

		const ROUTE_ADMIN				= 'admin';
		const ROUTE_SITE				= 'site';

		const ROUTES = [
			1							=> self::ROUTE_ADMIN,
			2							=> self::ROUTE_SITE
		];

		const ENTRIES = [
			1							=> 'html',
			2							=> 'xhr'
		];

	}